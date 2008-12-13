/* Gearman server and library
 * Copyright (C) 2008 Brian Aker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define TEST_INTERNAL 1

#include "test.h"
/* Prototypes */
long int timedif(struct timeval a, struct timeval b);

long int timedif(struct timeval a, struct timeval b)
{
  register int us, s;

  us = a.tv_usec - b.tv_usec;
  us /= 1000;
  s = a.tv_sec - b.tv_sec;
  s *= 1000;
  return s + us;
}

int main(int argc, char *argv[])
{
  unsigned int x;
  char *collection_to_run;
  char *wildcard;
  world_st world;
  collection_st *collection;
  void *collection_object= NULL;
  collection_st *next;
  long int load_time;

  memset(&world, 0, sizeof(world_st));
  get_world(&world);
  collection= world.collections;


  if (world.create)
    collection_object= world.create();


  if (argc > 1)
    collection_to_run= argv[1];
  else
    collection_to_run= NULL;

  if (argc == 3)
    wildcard= argv[2];
  else
    wildcard= NULL;

  srandom(time(NULL));

  for (next= collection; next->name; next++)
  {
    test_st *run;

    run= next->tests;
    if (collection_to_run && strcmp(collection_to_run, next->name))
      continue;

    printf("\n%s\n\n", next->name);

    for (x= 0; run->name; run++)
    {
      struct timeval start_time, end_time;
      void *object= NULL;

      if (wildcard && strcmp(wildcard, run->name))
        continue;

      printf("Testing %-50s", run->name);

      if (run->requires_flush && next->flush)
        next->flush();

      if (next->create)
        object= next->create(collection_object);

      if (next->pre)
      {
        test_return rc;
        rc= next->pre(object);

        if (rc != TEST_SUCCESS)
        {
          printf("[ skipping ]\n");
          goto error;
        }
      }

      gettimeofday(&start_time, NULL);
      assert(object);
      run->function(object);
      gettimeofday(&end_time, NULL);
      load_time= timedif(end_time, start_time);
      printf("[ ok %ld.%03ld ]\n", load_time / 1000, 
              load_time % 1000);

      if (next->post)
        (void)next->post(object);

error:
      if (next->destroy)
        next->destroy(object);
    }
  }

  if (world.destroy)
    world.destroy(collection_object);

  printf("All tests completed successfully\n\n");

  return 0;
}
