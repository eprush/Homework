#include <iostream>
#include <condition_variable>
#include <algorithm>
#include <vector>
#include <thread>
#include <future>
#include <cmath>
#include <memory>
#include <mutex>
#include <queue>

template < typename T, class Container = std::vector<T>,
	                   class Comparator = std::less< typename Container::value_type > >
class Threadsafe_Queue
{
public:
	using size_type = typename Container::size_type;
	using lock_type = std::unique_lock<std::mutex>;

	Threadsafe_Queue() = default;

	Threadsafe_Queue(const Threadsafe_Queue& other_queue)
	{
		std::lock_guard < std::mutex > lock(other_queue.m_mutex);
		m_queue = other_queue.m_queue;
	}

	Threadsafe_Queue& operator=(const Threadsafe_Queue& other_queue)
	{
		lock_type m_lock(m_mutex, std::defer_lock);
		lock_type other_lock(other_queue.m_mutex, std::defer_lock);
		std::lock(m_lock, other_lock);

		/*std::scoped_lock lock(m_mutex, other_queue.m_mutex);*/
		m_queue = other_queue.m_queue;
	}

public:
	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_queue.push(value);
		m_condition_variable.notify_one();
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_queue.empty();
	}

	void swap(Threadsafe_Queue& other_queue) noexcept
	{
		lock_type m_lock(m_mutex, std::defer_lock);
		lock_type other_lock(other_queue.m_mutex, std::defer_lock);
		std::lock(m_lock, other_lock);

		m_queue.swap(other_queue.m_queue);
	}

	size_type size()
	{
		return this->empty();
	}

public:
	void wait_and_pop(T& value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this]() {return !m_queue.empty(); });
		value = m_queue.top();
		m_queue.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);

		m_condition_variable.wait(lock, [this] {return !m_queue.empty(); });
		auto result = std::make_shared < T >(m_queue.top());
		m_queue.pop();

		return result;
	}

	bool try_pop(T& value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_queue.empty())
			return false;

		value = m_queue.top();
		m_queue.pop();

		return true;
	}

	std::shared_ptr < T > try_pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_queue.empty())
			return std::shared_ptr < T >();

		auto result = std::make_shared < T >(m_queue.top());
		m_queue.pop();

		return result;
	}

private:
	std::priority_queue < T, Container, Comparator > m_queue;
	std::condition_variable                          m_condition_variable;
	mutable std::mutex                               m_mutex;
};

void fill_queue(Threadsafe_Queue<int>& queue)
{
	std::vector<std::thread> push_threads(7);
	int x = 0;
	for (auto begin = std::begin(push_threads); begin != std::end(push_threads); std::advance(begin, 1))
	{
		std::cin >> x;
		std::packaged_task<void(int)> task([&queue](int x) {queue.push(x); });
		*begin = std::thread(std::move(task), x);
	}

	for (auto begin = std::begin(push_threads); begin != std::end(push_threads); std::advance(begin, 1))
	{
		(*begin).join();
	}
}

int pop_queue(Threadsafe_Queue<int>& queue)
{
	int q = 0;

	std::packaged_task<void(int&)> task([&queue](int& x) {queue.wait_and_pop(x); });
	std::thread pop = std::thread(std::move(task), std::ref(q));
	pop.join();

	return q;
}

int main()
{
	Threadsafe_Queue<int> queue_1;

	/*Threadsafe_Queue<int, std::vector<int>, std::greater< int > > queue_2;*/
	Threadsafe_Queue<int> queue_2;

	fill_queue(queue_1);
	fill_queue(queue_2);

	queue_1.swap(queue_2);
	int q_1 = pop_queue(queue_1);
	int q_2 = pop_queue(queue_2);
	std::cout << q_1 << " " << q_2 << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}