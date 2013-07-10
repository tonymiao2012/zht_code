/*
 * Copyright 2010-2020 DatasysLab@iit.edu(http://datasys.cs.iit.edu/index.html)
 *      Director: Ioan Raicu(iraicu@cs.iit.edu)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of ZHT library(http://datasys.cs.iit.edu/projects/ZHT/index.html).
 *      Ioan Raicu(iraicu@cs.iit.edu),
 *      Tonglin Li(tli13@hawk.iit.edu) with nickname Tony,
 *      Xiaobing Zhou(xzhou40@hawk.iit.edu) with nickname Xiaobingo.
 *
 * ip_server.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: Xiaobingo
 *      Contributor: Tony
 */

#include "ip_server.h"

#include  "ProxyStubFactory.h"

#include <string.h>
#include <stdio.h>

IPServer::IPServer() {
}

IPServer::~IPServer() {
}

void IPServer::process(const int& fd, const char * const buf, sockaddr sender) {

	ProtoStub *stub = ProxyStubFactory::createStub();

	if (stub == 0) {

		fprintf(stderr,
				"IPServer::process(): error on ProxyStubFactory::createStub().\n");
		return;
	}

	ProtoAddr pa;
	pa.fd = fd;
	pa.sender = &sender;

	stub->recvsend(pa, buf);
}

