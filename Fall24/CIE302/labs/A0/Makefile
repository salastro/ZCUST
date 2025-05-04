CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -pthread

PRODUCER = producer
CONSUMER = consumer
COMMON = common.h

all: $(PRODUCER) $(CONSUMER) $(COMMON)

$(PRODUCER): producer.c $(COMMON)
	$(CC) $(CFLAGS) -o $(PRODUCER) producer.c

$(CONSUMER): consumer.c $(COMMON)
	$(CC) $(CFLAGS) -o $(CONSUMER) consumer.c

clean:
	rm -f $(PRODUCER) $(CONSUMER)
