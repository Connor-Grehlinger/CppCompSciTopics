#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //Data structure for number of times a particular string appears
  //Must hold the string in question and the count of it
  char * string; //  string
  unsigned int count;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t ** counts; // reference to an array of one_counts
  unsigned int num_counts;
  unsigned int num_unknowns;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);
int isIn(counts_t * c, const char * name);
void freeCounts(counts_t * c);

#endif
