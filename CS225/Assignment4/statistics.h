#ifndef STATISTICS_H
#define STATISTICS_H
#include <vector>    //vector
#include <algorithm> //copy
#include <ostream>   //ostream
#include <istream>   //istream
#include <map>       //map
#include <iostream> //cout

typedef std::map<int, int> MapContainer;
typedef std::vector<int> ContainerType;
typedef std::pair< ContainerType::iterator, ContainerType::iterator > EqualBounds;

class NextInt
{
  public:
  
    NextInt(int value_) : value(value_) {}
  
    int operator()(void)
    {
      return value++;
    }
      
  private:
    int value;
};

class HistogramFill
{
  public:
  
  HistogramFill(ContainerType& fill_, ContainerType& data_, int range_) :
  fill(fill_), data(data_), range(range_), iteration(0) {}
  
  void operator()(int bin_num)
  {
      // determine which bin supposed to fill
      // this is the minimum value in the bin (inclusive)
    int low_range = range * bin_num;
    
      // this is the maximum value for this bin (exclusive)
    int high_range = low_range + range;
    
      // find where to start searching for data
    ContainerType::iterator low_bound = 
      std::lower_bound(data.begin(), data.end(), low_range);
    
      // find last piece for this bin
    ContainerType::iterator high_bound = 
      std::lower_bound(data.begin(), data.end(), high_range);
    
      // stuff differnece into bin slot
    fill[iteration] = std::distance(low_bound, high_bound);
    
      // set lowbound further in the vector for subsequent call
    low_bound = high_bound;
    
      // increment counter
    iteration++;
  }
  
  private:
  
    // container to fill int
  ContainerType& fill;
  
    // data to iterate on
  ContainerType& data;
  
    // range of values per bin
  int range;
  
    // remember which slot to stuff result in in fill
  int iteration;
  
};


class Occurency
{
  public:
  
    void operator()(int data);
  
    Occurency(int mult, MapContainer& init, ContainerType& vector_) : 
    
    multiplicity(mult), map(init), vector(vector_) {}
  
  private:
    int multiplicity;
    
    MapContainer& map;
    
    ContainerType& vector;
};
  
class Statistics {
    private:
        ContainerType data;
    public:
        Statistics();
  
        template <typename T> 
        Statistics( T const* b, T const* e );
        
        friend std::ostream& operator<<( std::ostream& out, Statistics const& stat );
        
        friend std::istream& operator>>( std::istream& in, Statistics & stat );
  
        double Average() const;
  
        int Maximum() const;
        int Minimum() const;
  
        double Deviation() const;
  
        template <typename T>
        void RemoveIf(T function);
  
        std::vector<int> Histogram(int bin_num, int low_range, int high_range);
  
        void DrawHistogramH(int bin_num, int low_range, int high_range);
        
        void DrawHistogramV(int, int, int) {}
  
        std::map<int,int> OccuresMoreThan(int occurence) const;
        
};

template <typename T>
void Statistics::RemoveIf(T function)
{
    // find place to delete from
  ContainerType::iterator endpoint = remove_if(data.begin(), data.end(), function);
  
    // delete from enpoint -> end of vector
  data.erase(endpoint, data.end());
  
    // swap trick to shrink vector
  ContainerType(data).swap(data);
  
  //std::cout << data.size() << " " << data.capacity () << std::endl;
}
  
  
template <typename T>
Statistics::Statistics( T const* b, T const* e ) : data(e-b) {
    std::copy( b, e, data.begin() ); // we can use regular pointers to specify ranges!
  

}

#endif
