#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>

namespace templates{
    //Function templates can be used for different data types
    /**
     * @brief Making a template to find the max of the two inputs
     * 
     * @tparam T 
     * @param x 
     * @param y 
     * @return T 
     */
    template <typename T> T myMax(T x, T y){
        return (x>y) ? x:y;
    }
    /**
     * @brief // We can use this for any data type that supports
    // comparison operator < and swap works for it.
    * 
    */
    template <class T> void bubbleSort(T a[], int n){
        for (int i = 0; i < n - 1; i++)
            for (int j = n - 1; i < j; j--)
                if (a[j] < a[j - 1])//swap values if next val is smaller than next
                    std::swap(a[j], a[j - 1]);
    }
    /**
     * @brief Class templates useful when a class defines something 
     * that is independent of the datatype
     * 
     * @tparam T 
     */
    template <typename T> class Array{
        private :
            T* ptr; //pointer
            int size ;//size of array
        public:
            Array(T arr[], int s);// default constructor
            void print();//method to print
    };
    /**
     * @brief Construct a new Array< T>:: Array object
     * @tparam T 
     * @param arr //array
     * @param s //size
     */
    template<typename T> Array<T>::Array(T arr[],int s){
        ptr= new T[s];
        size=s;
        for(int i=0;i<size;i++)
            ptr[i]=arr[i];
    } 
    template <typename T> void Array<T>::print(){
        for(int i=0;i<size;i++)
            std::cout<<" "<<*(ptr+i);
        std::cout<<std::endl;
    }
    // /**
    //  * @brief A constrcutor
    //  * templete can have more than one argument
    //  * 
    //  * @tparam T 
    //  * @tparam U 
    //  */
    // template<class T, class U> class A{
    //     T x;
    //     U y;
    //     public:
    //         A(){std::cout<< "Default Constructor called"<<std::endl;}
    // };
    /**
     * @brief Specifying default value for templates
     * 
     * @tparam T 
     * @tparam U 
     */
    template<class T, class U=char> class A{
        T x;
        U y;
        public:
            A(){std::cout<< "Default Constructor called"<<std::endl;}
    };
    /**
     * @brief demonstrate working with non-type parameters to templates
     * find the min value in array
     * 
     * @tparam T 
     * @tparam max 
     * @param arr 
     * @param n 
     * @return int 
     */
    template<class T, int max> int arrMin(T arr[], int n){
        int m=max;
        for(int i=0;i<n;i++)
            if(arr[i]<m)
                m=arr[i];
        return m;
    }
    /**
     * @brief how different data types using constructor and template
     * 
     * @tparam T 
     */
    template<class T> class info{
        public:
            info(T A)//constructor of type template
            {
                std::cout<<"\n"<<"A = "<<A<<" size of data in bytes: "<<sizeof(A);
            }
    };
    /**
     * @brief Function Templates and static variables
     * each instation of a function templates has its own copy of local static variables
     * 
     * @tparam T 
     * @param x 
     */
    template<typename T> void fun(const T & x){
        static int i=10;
        std::cout<<++i;
        return;
    }
    /**
     * @brief spealized function templates
     * 
     * @tparam T 
     * @param x 
     */
    template<typename T> void fun(int x){
    
        std::cout<<"Spealised template for int type"<<std::endl;
        return;
    } 

    /**
     * @brief Class templates and static variables
     * 
     * @tparam T 
     */
    template<class T> class Test{
        private: 
            T val;
        public:
            static int count;
            Test(){
                count++;
            }
    };
    template<class T> int Test<T>::count=0;
    
    /**
     * @brief spealised class template
     * 
     * @tparam  
     */
    template<>class Test<int>{
        public:
            Test(){
                std::cout<<"Spealized class template"<<std::endl;
            }
    };

    /**
     * @brief Template MetaProgramming-any computation expressible by a computer program can be computed in some form
     * Program executes 2 raised to the power n
     * Calculation is done at compile time
     * 
     * @tparam n 
     */
    template<int n> struct funStruct{
        enum { val=2*funStruct<n-1>::val};
    };
    template<>struct funStruct<0>{
        enum{val=1};
    };
    
}
namespace Functors{
    /**
     * @brief //copy if functor
     * 
     * @tparam T 
     */
    template< typename T> class not_equal_to{
        public:
            not_equal_to(const T & cmp_val):cmp_ptr(& cmp_val){}//copy constructor
            //overload the () operator
            bool operator()(const T & container_val)const{//read only no changes
                return *cmp_ptr !=container_val;
            }
            const T * cmp_ptr; //aboid deep copies by storing a ptr
    };
    /**
     * @brief for each functor
     * 
     * @tparam T 
     */
    template<typename T> class bit_examiner{
        public:
            bit_examiner(std::size_t which_bit): count(0), bit(which_bit){} //default constractor
            bit_examiner(const bit_examiner & rhs): count(rhs.count),bit(rhs.bit){}//copy constructor
            //count all occuracnces of specified bit here
            //overload () operator
            void operator()(const T & value)
            {if(value & (0x1 << bit)) ++count;}
            std::size_t count;
            std::size_t bit;
    };

    /**
     * @brief Transform functor
     * 
     * @tparam T 
     */
    template<typename T> class add_to{
    public:
        add_to(const T & value): ptr(& value){}//copy constructor
        //count all occuracnces of specified bit here
        //overload () operator
        T operator()(const T & value)const
        {return *ptr+ value;}//add value
        const T * ptr;
    };

    class customFunctor{
        public:
            int operator()(const int & x)const{
                return x*3;
            }
    };
}
int main(){
    //Function templates can be used for different data types:
    // //check max value for integers:
    // std::cout<<"Max int value is: "<<templates::myMax<int>(3,7)<<std::endl;
    // //check max value for doubles:
    // std::cout<<"Max double value is: "<<templates::myMax<double>(3.00,7.00)<<std::endl;
    // //check max value for chars:
    // std::cout<<"Max char value is: "<<templates::myMax<char>('a','z')<<std::endl;

    //Function templates:
    //bubble sort
    // int a[5]={10,50,30,40,20};
    // int n=sizeof(a)/sizeof(a[0]);
    // //call template bubble sort
    // templates::bubbleSort<int>(a,n);
    // std::cout<< "Sorted array: ";
    // for(auto i :a )
    //     std::cout<< i <<" "<<std::endl;

    //Class templates:
    // int arr[5]={1,2,3,4,5};
    // templates::Array<int> a(arr,5);
    // a.print();
    
    //Class templates with more than one argument:
    // templates::A<char,char>a;
    // templates::A<int,double>b;
    //Class templates with specified argument:
    // templates::A<char>a;

    //working with non-type parameters to templates:
    // int arr1[]={10,20,15,12};
    // int n1=sizeof(arr1)/sizeof(arr1[0]);
    // int arr2[]={1,2,3};
    // int n2=sizeof(arr2)/sizeof(arr2[0]);
    // std::cout<<templates::arrMin<int,1000>(arr1,n1)<<std::endl;
    // std::cout<<templates::arrMin<int,256>(arr2,n2)<<std::endl;
    
    //how different data types using templates and constructors:
    // //passing character value by creating an object
    // templates::info<char>p('x');
    // //passing integer value by creating an object
    // templates::info<int>q(22);
    // //passing float value by creating an object
    // templates::info<float>r(2.25);

    //function templates and static variables
    // templates::fun<int>(1);
    // std::cout<<std::endl;
    // templates::fun<int>(2);
    // std::cout<<std::endl;
    // templates::fun<double>(1.1);
    // std::cout<<std::endl;
    // getchar();

    //Class templates and static variables
    // templates::Test<int>a; //count =1
    // templates::Test<int>b;//count=2
    // templates::Test<double>c;//count=1
    // std::cout<<templates::Test<int>::count<<std::endl;
    // std::cout<<templates::Test<double>::count<<std::endl;
    
    //Specialized Templates for functions and classes
    // templates::fun<int>(2);
    // templates::fun<double>(1.1);
    // std::cout<<std::endl;
    // templates::Test<int>a;
    // templates::Test<char>b;

    //Copy if Functor
    // std::vector<int> data={0,1,2,3,4}; //initialise a list
    // std::vector<int> result;
    // Functors::not_equal_to<int> net(3); //construct a functor
    // std::cout<< (net(3)==false);//call net.operator(3) {return 3 !=3;}
    // std::cout<< (net(2)==true);//call net.operator(2) {return 3 !=2;}
    // //copies everything except 3
    // std::copy_if(data.begin(),data.end(),std::back_inserter(result), net);
    
    // for(auto it=result.begin();it!=result.end();++it){
    //     std::cout<<*it<<std::endl;
    // }

    // // For each functor:
    // std::vector<int> data2={0,1,2,3,4}; //initialise a list
    // Functors::bit_examiner<int> functor(6);
    // std::for_each(data2.begin(),data2.end(),functor);
    // std::cout<<functor.count<<std::endl;

    // //Transform:
    // std::vector<int> data={0,1,2,3,4}; //initialise a list
    // std::vector<int> result;
    // Functors::add_to<int> add(5);
    // std::transform(data.begin(),data.end(),std::back_inserter(result),add);
    // for(auto it=result.begin();it!=result.end();++it){
    //     std::cout<<*it<<std::endl;
    // }

    //2018 Transform functor without templates
    std::vector<int> data={0,1,2,3,4}; //initialise a list
    std::vector<int> result;
    std::transform(data.begin(),data.end(),std::back_inserter(result),Functors::customFunctor());
    for(auto it=result.begin();it!=result.end();++it){
        std::cout<<*it<<std::endl;
    }
   
    return 0;
}

