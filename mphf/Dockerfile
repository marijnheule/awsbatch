FROM amazonlinux:latest

RUN yum -y install which unzip aws-cli clang git zlib-devel mpi openmpi-devel make
RUN pip3 install --upgrade awscli && pip3 install --upgrade boto3

RUN git clone https://github.com/arminbiere/cadical.git /tmp/cadical
RUN cd /tmp/cadical; ./configure; make
RUN mkdir /tmp/solvers; cp /tmp/cadical/build/cadical /tmp/solvers/cadical
RUN git clone https://github.com/marijnheule/CnC.git /tmp/CnC
RUN cd /tmp/CnC; ./build.sh; cp /tmp/CnC/march_cu/march_cu /tmp/solvers/march_cu; cp /tmp/CnC/iglucose/core/iglucose /tmp/solvers/iglucose
ADD mphf /tmp/mphf
RUN cd /tmp/mphf; make
RUN mkdir /tmp/bin; cp /tmp/mphf/cnf/encode /tmp/bin/; cp /tmp/mphf/decode/decode /tmp/bin/
ADD scripts /tmp/scripts
RUN mkdir /tmp/log; mkdir /tmp/cnf; mkdir /tmp/cubes


WORKDIR /tmp
RUN chown -R nobody:nobody /tmp

ENV PATH "$PATH:/tmp/solvers"
ENV PATH "$PATH:/tmp/bin"
ENV PATH "$PATH:/tmp/scripts"

USER nobody
