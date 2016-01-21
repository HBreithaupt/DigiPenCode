#include "statistics.h"
#include <numeric> //accumulate
#include <cmath> //sqrt
#include <iterator> //ostream_iterator, back_inserter
#include <iomanip> //setfill setw
#include <functional>

Statistics::Statistics() : data() {}
  

void PrintHistogram(int value)
{
    // use setw and setfill to print correct number of 
    // astericks in on eprint statement
 std::cout << std::setw (value) << std::setfill('*');
 std::cout << '*' << std::endl;
}

void Occurency::operator()(int data)
{ 
  // THIS WILL ONLY WORK ON SORTED VECTORS, BEHAVIOR WILL BE INCORRECT
  // ON UNSORTED VECTORS
  
    // get iterator to first piece of data requested
    // (most likely first element of vector)
    // this is marked static to preserve place in vector
    // for immediate recalls, location of iterator
    // will be updated inside function to account for this
  ContainerType::iterator first = std::find(vector.begin(), vector.end(), data);
  
    // get a pair of iterators that is the distance of repeated data
  EqualBounds result = std::equal_range(first, vector.end(), data);
  
    // if distance is greater than repetions required
    // record it in map
  if(result.second - result.first > multiplicity)
    map.insert(std::pair<int,int>(data,result.second - result.first));
  
    // update first pointer to remember position in vector
  first = result.second;
}

double deviation_enum(double average_, int data)
{
    // hold sum of iteration
  static double sum = 0;
  static double average = average_;
  
    // calulate (x_i - a)^2 part of deviation
  sum += (data - average) * (data - average);
  
    // return sigma (x_i -a)^2
  return sum;
  
}

double Statistics::Average() const
{
    // hold sum of vector
  double sum;
  
    // calc sum of vector
  sum = std::accumulate(data.begin(), data.end(), 0);
  
    // return average of the vector
  return sum / data.size();
  
}

int Statistics::Maximum() const
{
    // return max elemeint in container
  return *std::max_element(data.begin(), data.end());
}

int Statistics::Minimum() const
{
    // return min element in container
  return *std::min_element(data.begin(), data.end());
}

double Statistics::Deviation() const
{
    // find average of vector
  double average = Average();
  
    // calc sigma (x_i - a)^2
  double sigma = std::accumulate(data.begin(), data.end(), average, deviation_enum);
  
    // return sqrt ( 1/n * sigma (x_i - a)^2 )
  return sqrt( 1.0 / data.size() * sigma );
  
}

std::map<int,int> Statistics::OccuresMoreThan(int occurence) const
{
    // map to store answers
  std::map<int,int> map;
  
    // copy vector
  ContainerType copy(data);
  
    // sort the copy
  std::sort(copy.begin(),copy.end());
  
    // decalare functor and initialize data needed
    // needs occurence requirement
    // pointer to map storing answer
    // and reference to vector
  Occurency result(occurence, map, copy);
  
    // iterate over vector using for each and functor
  std::for_each(copy.begin(),copy.end(), result);
  
    // return map, filled out by for_each
  return map;
}


std::vector<int> Statistics::Histogram(int bin_num, int low_range, int high_range)
{
    // calulate range each bin is supposed to contain;
  int range = high_range / bin_num;
  
    // hold results
  ContainerType bins(bin_num);
  
  
    // copy data
  ContainerType copy(data);
  
    // sort the data
  std::sort(copy.begin(), copy.end(), std::less<int>());
  
    // declare functor that has pointers to vector to 
    // fill in (bins) 
    // vector w/ data to read form (copy)
    // and range each bin is supposed to have (range)
  HistogramFill filler(bins, copy, range);
  
    // number bins 0 - (n-1) for
    // use in for_each loop coming up
  std::generate(bins.begin(), bins.end(), NextInt(low_range));
  
    // fill in each bin using bin index as indicator for values
  std::for_each(bins.begin(), bins.end(), filler);
  
    // return vector containing the results
  return bins;
}
  
void Statistics::DrawHistogramH(int bin_num, int low_range, int high_range)
{
    // fill out a vector with histogrm information
  std::vector<int> bins = Histogram(bin_num, low_range, high_range);
  
    // print the histogram
  for_each(bins.begin(), bins.end(), PrintHistogram);
}
  
std::ostream& operator<<( std::ostream& out, Statistics const& stat ) 
{
    std::copy( stat.data.begin(),  stat.data.end(),
               std::ostream_iterator<int>( out, " " ) );
    return out;
}

std::istream& operator>>( std::istream& in, Statistics & stat ) 
{
    std::copy( std::istream_iterator<int>(in),
               std::istream_iterator<int>(),
               std::back_inserter( stat.data ) );
    return in; 
}

