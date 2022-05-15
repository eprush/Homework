#pragma once
#define BOOST_DATE_TIME_NO_LIB
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace boost::interprocess;

class Chat
{
private:
    using shared_memory_t    = managed_shared_memory;
    using manager_t          = shared_memory_t::segment_manager;

    using string_allocator_t = allocator    < char, manager_t >;
    using string_t           = basic_string < char, std::char_traits < char >, string_allocator_t>;

    using vector_allocator_t = allocator < string_t, manager_t >;
    using vector_t           = vector    < string_t, vector_allocator_t>;

    using mutex_t            = interprocess_mutex;
    using condition_t        = interprocess_condition;

    using counter_t          = std::atomic < std::size_t >;

public:
    explicit Chat(const std::string& user_name):m_user_name(user_name), m_exit_flag(false),
        m_shared_memory(shared_memory_t(open_or_create, shared_memory_name.c_str(), 1024)),
        m_local_messages(0)
    {
        m_vector    = m_shared_memory.find_or_construct < vector_t    >("Vector")   (m_shared_memory.get_segment_manager());
        m_mutex     = m_shared_memory.find_or_construct < mutex_t     >("mutex")    ();
        m_condition = m_shared_memory.find_or_construct < condition_t >("condition")();
        m_users     = m_shared_memory.find_or_construct < counter_t   >("users")    (0);
        m_messages  = m_shared_memory.find_or_construct < counter_t   >("messages") (0);
        (*m_users)++;

    }

    ~Chat() noexcept = default;

public:
    void run()
    {
        auto reader = std::thread(&Chat::read, this);

        write();

        send_message(m_user_name + " left the chat");

        reader.join();
        if ( !(--(*m_users)) )
        {
            std::cout << "no one in the chat" << std::endl;
            shared_memory_object::remove(shared_memory_name.c_str());
        }
    }

private:
    void read()
    {
        show_history();
        send_message(m_user_name + " joined the chat");

        while (true)
        {
            scoped_lock < mutex_t > lock(*m_mutex);
            m_condition->wait(lock, [this]() { return (*m_messages - m_local_messages > 0 || m_exit_flag); });

            if (m_exit_flag)
                break;

            std::cout << m_vector->back() << std::endl;
            ++m_local_messages;
        }
    }

    void show_history()
    {
        std::cout << "count of all messages equals " << *m_messages << std::endl;
        scoped_lock<mutex_t> lock(*m_mutex);
        for (const auto& message : *m_vector)
        {
            std::cout << message << std::endl;
            ++m_local_messages;
        }
    }

    void send_message(const std::string& message)
    {
        scoped_lock<mutex_t> lock(*m_mutex);

        m_vector->push_back( string_t(message.c_str(), m_shared_memory.get_segment_manager()) );

        ++(*m_messages), ++m_local_messages;

        m_condition->notify_one();
    }

    void write()
    {
        std::string message = "";
        while (true)
        {
            std::getline(std::cin, message);

            if (message == exit_word)
            {
                m_exit_flag = true;
                break;
            }
            else
            {
                send_message(message);
            }
        }

    }

private:
    static inline const std::string shared_memory_name = "shared_memory";
    static inline const std::string exit_word          = "/exit";

private:
    std::string          m_user_name;
    std::atomic < bool > m_exit_flag;
    shared_memory_t      m_shared_memory;

    vector_t*    m_vector;
    mutex_t*     m_mutex;
    condition_t* m_condition;
    counter_t*   m_users;
    counter_t*   m_messages;

    std::size_t  m_local_messages;
};