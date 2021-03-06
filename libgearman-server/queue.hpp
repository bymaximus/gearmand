/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  Gearmand client and server library.
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include <string>

struct gearmand_st;

namespace boost { namespace program_options { class options_description; } }

namespace gearmand {

namespace plugins { class Queue; }

namespace queue {

void add(plugins::Queue* queue);
void load_options(boost::program_options::options_description &all);
gearmand_error_t initialize(gearmand_st *gearmand, std::string);

} // namespace queue
} // namespace gearmand

namespace gearmand { namespace queue { class Context; } }

/**
 * Set persistent queue context that will be passed back to all queue callback
 * functions.
 */
void gearman_server_set_queue(gearman_server_st& server,
                              void *context,
                              gearman_queue_add_fn *add,
                              gearman_queue_flush_fn *flush,
                              gearman_queue_done_fn *done,
                              gearman_queue_replay_fn *replay);

void gearman_server_set_queue(gearman_server_st& server,
                              void *context,
                              gearman_queue_add_fn *add,
                              gearman_queue_flush_fn *flush,
                              gearman_queue_done_fn *done,
                              gearman_queue_replay_fn *replay,
							  gearman_queue_job_exists_by_unique_fn *job_exists_by_unique);



void gearman_server_set_queue(gearman_server_st& server,
                              gearmand::queue::Context* context);
