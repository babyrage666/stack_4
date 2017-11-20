#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
class Stack
{
public:
	Stack() noexcept : Stack(2) {} //конструктор по умаолчанию (размер = 2)
    Stack(size_t cap) noexcept : array_size_(cap), count_(0), array_(new T[cap]) {} // конструктор с параметром

	//copy c-tor
	Stack(const Stack& rhs) noexcept : array_(new T[rhs.array_size_]), array_size_(rhs.array_size_), count_(rhs.count_) 
	{
		copy(rhs.array_, rhs.array_ + rhs.array_size_, array_);
	}
	
	//move c-tor
	Stack(Stack&& rhs) noexcept : array_(rhs.array_), array_size_(rhs.array_size_), count_(rhs.count_) 
	{
		rhs.array_ = nullptr;
		rhs.array_size_ = 0;
		rhs.count_ = 0;
	}
	
	//stack initializer
	Stack(initializer_list<T> l) : array_size_ {l.size()}, count_{l.size()}, array_{new T[array_size_]}
    {
        copy(l.begin(), l.end(), array_);
    }

	
	// swap значений переменных
	void swap(Stack& rhs) noexcept 
	{
		std::swap(this->array_, rhs.array_);
		std::swap(this->array_size_, rhs.array_size_);
		std::swap(this->count_, rhs.count_);
	}
	
	Stack& operator=(const Stack& rhs) noexcept //оператор присваивания копирования
	{
		if(this != &rhs)
			Stack(rhs).swap(*this); 
		return *this;
	}
	
	Stack& operator=(Stack&& rhs) noexcept //опеатор присваивания перемещения
	{
		if(this != &rhs)
			Stack(move(rhs)).swap(*this);
		return *this;
	}
	
    size_t count() const noexcept// метод возврата privete переменной
    {
        return count_;
    }
	
	T& operator[](size_t pos) 
	{
        return array_[pos];
    }
	
    void push(T const &value) noexcept // добавление эл-та в стек
    {
        if(count_ == array_size_)
        {
            cout<<"stack overflowed: adding new memory\n";
            T* new_array_ = new T[array_size_*2];
            for(size_t i =0; i < array_size_; ++i)
                new_array_[i] = array_[i];
			array_size_ *= 2;
            delete[] array_;
            array_ = new_array_;
        }
        array_[count_++] = value;
    }
    
    void pop() noexcept//удаление элемента
    {
        if(count_ == 0)
            throw runtime_error("stack is empty");
		--count_; 
    }
	
	bool empty() const noexcept
	{
        if(count() == 0) 
			return true;
        return false;
	}
	
	T top() const noexcept 
	{
		if (count_ == 0)
            throw runtime_error("stack is empty\n");
        
        size_t c = count_ - 1;
        return array_[c]
	}
	
	T& operator[](size_t a) const noexcept 
	{
		return array_[a];
	}
	
	friend auto operator<<(ostream& out, const Stack& rhs)->ostream& 
	{
        if (rhs.array_ == nullptr) 
			out << "Epmty stack"; 
        else 
		{
            out << "{";
            for (size_t i = 0; i < rhs.count_; ++i) 
			{
                out <<  " " <<  rhs.array_[i];
            }
            out << " " << "}";
        }
        return out;
    }
	
    virtual ~Stack() { delete[] array_; } // вирутальный деструктор
private:
    T * array_;
    size_t array_size_;
    size_t count_;
};