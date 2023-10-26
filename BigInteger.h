#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct BigInteger
{
    struct node *head;
    int length;
};

struct node *newnode(int d);
struct BigInteger initialise(char *s);
void reverseLinked(struct node **head);
void display(struct BigInteger ab);
struct node *terminateZeroes(struct node *head);
int getdividend(struct node **p1, int l);
int toNumber(struct node *head);
int length(struct node *head);
struct node *add1linked(struct node *p1, struct node *p2);
struct BigInteger add1(struct BigInteger a, struct BigInteger b);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub1(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul1(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct node *divide1(struct node *p1, struct node *p2);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);

#endif