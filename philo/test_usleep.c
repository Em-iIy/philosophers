#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include "test.h"

long long   convert_to_us(const struct timeval time)
{
   long long  time_in_us;

   time_in_us = time.tv_sec * 1000000;
   time_in_us += time.tv_usec;
   return (time_in_us);
}

static int  time_since_in_usec(const struct timeval since)
{
   struct timeval current;
   int             time_diff;

   if (gettimeofday(&current, NULL) == -1)
   {
      printf("Gettimeofday error\n");
      return (-1);
   }
   time_diff = convert_to_us(current) - convert_to_us(since);
   return (time_diff);
}

int    ft_usleep(suseconds_t sleep_time)
{
   struct timeval start;
   int             time_diff;

   time_diff = 0;
   if (gettimeofday(&start, NULL) == -1)
   {
      printf("Gettimeofday error\n");
      return (0);
   }
   while (time_diff < (int) sleep_time)
   {
      usleep(10);
      time_diff = time_since_in_usec(start);
      if (time_diff == -1)
         return (0);
   }
   return (1);
}