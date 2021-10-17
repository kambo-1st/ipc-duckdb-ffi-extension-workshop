FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Berlin

RUN apt-get update && \
    apt-get -y install \
            libzip-dev \
            zlib1g-dev \
            nano \
            git \
            tzdata \
            build-essential \
            autoconf \
            automake \
            gdb \
            libffi-dev \
            libssl-dev \
            bison \
            re2c \
            libxml2-dev \
            pkg-config \
            libsqlite3-dev \
            libonig-dev \
            curl \
            valgrind \
            gosu \
            sudo \
            unzip && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN mkdir /data && \
    cd /data && \
    git clone https://github.com/php/php-src.git

RUN cd /data/php-src && \
    git checkout php-8.0.8 && \
    rm -rf .git && \
    ./buildconf --force && \
    ./configure --enable-debug --enable-mbstring --with-zip --with-zlib --disable-phpdbg --disable-phpdbg-webhelper --enable-opcache --with-ffi && \
    make -j4 && \
    make install

RUN cd /tmp/ && \
    curl -L -o "./libduckdb.zip" https://github.com/duckdb/duckdb/releases/download/v0.2.8/libduckdb-linux-amd64.zip && \
    unzip libduckdb.zip && \
    mkdir /usr/local/lib/duckdb && \
    cp libduckdb.so /usr/local/lib/duckdb && \
    cp duckdb.h /usr/local/lib/duckdb

# Add local user 'dev'
RUN groupadd -r dev --gid=9001 && useradd -r -g dev --uid=9001 dev
# Grant him sudo privileges
RUN echo "dev ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/dev && \
    chmod 0440 /etc/sudoers.d/dev

# Do stuff with this user if needed
USER dev
ENV HOME /home/dev
WORKDIR $HOME

# Repass root
USER root

RUN echo 'alias ll="ls -all"' >> /home/dev/.bashrc

# Copy entrypoint
COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN ["chmod", "+x", "/usr/local/bin/docker-entrypoint.sh"]
ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]

CMD ["bash"]
