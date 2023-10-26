#include "BigInteger.h"

struct node *newnode(int d){

    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (!temp)
    {
        printf("error allocating \n");
        return NULL;
    }
    temp->data = d;

    temp->next = NULL;
    return temp;
}
struct BigInteger initialise(char *s){
    int i = 0, dat;

    struct BigInteger ab;
    ab.length = 0;
    ab.head = NULL;
    struct node *temp;

    while (s[i] != '\0')
    {

        dat = s[i] - 48;
        temp = newnode(dat);
        temp->next = ab.head;
        ab.head = temp;
        ab.length++;
        i++;
    }

    return ab;
}
void reverseLinked(struct node **head){
    struct node *node = *head, *nextnode;
    struct node *thead = NULL;
    thead = *head;
    while (node->next != NULL)
    {
        nextnode = node->next;
        node->next = node->next->next;
        nextnode->next = thead;
        thead = nextnode;
    }
    *head = thead;
}
void display(struct BigInteger ab){
    printf("THE INTEGER :\n");
    while (ab.head != NULL)
    {
        printf("%d  ", (ab.head->data));
        ab.head = (ab.head)->next;
    }
    printf("\n");
}
struct node *terminateZeroes(struct node *head){
    if (!head)
    {
        return head;
    }
    while (head->data == 0)
    {
        head = head->next;
    }
    return head;
}
int getdividend(struct node **p1, int l){
    int i = 0, div = 0;
    while (*p1 && i != l)
    {
        div = (div * 10) + (*p1)->data;
        i++;
        *p1 = (*p1)->next;
    }
    return div;
}
int toNumber(struct node *head){
    int number = 0;
    while (head)
    {
        number = (number * 10) + (head->data);
        head = head->next;
    }
    return number;
}
int length(struct node *head){
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}
struct node *add1linked(struct node *p1, struct node *p2){
    int l1, l2, tl, sum;
    int carry = 0;
    l1 = length(p1);
    l2 = length(p2);

    // reverseLinked(&p1);
    // reverseLinked(&p2);

    struct node *temp = NULL, *result = NULL, *itr = NULL;
    temp = (struct node *)malloc(sizeof(struct node));

    if (l2 > l1)
    {
        printf("error 4");
        temp = p1;
        p1 = p2;
        p2 = temp;
        tl = l1;
        l1 = l2;
        l2 = l1;
    }
    // result = (struct node *)malloc(sizeof(struct node));
    while (p1)
    {
        if (p2)
            sum = p1->data + p2->data + carry;
        else
            sum = p1->data + carry;
        carry = sum / 10;
        sum %= 10;
        temp = (struct node *)malloc(sizeof(struct node));
        temp->data = sum;
        temp->next = NULL;
        if (result == NULL)
        {
            result = temp;
            itr = result;
        }
        else
        {
            itr->next = temp;
            itr = itr->next;
        }
        p1 = p1->next;
        if (p2)
            p2 = p2->next;
    }
    if (carry)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        temp->data = carry;
        temp->next = NULL;
        itr->next = temp;
    }
    return result;
}
struct BigInteger add1(struct BigInteger a, struct BigInteger b){
    struct BigInteger result, temp;
    result.head = NULL;
    int sum, carry = 0, tl;
    struct node *itr, *itra, *itrb;
    itr = result.head;

    if (a.length < b.length)
    {
        temp = a;
        a = b;
        b = temp;
        tl = a.length;
        a.length = b.length;
        b.length = tl;
    }
    itra = a.head;
    itrb = b.head;
    while (itra)
    {
        if (itrb)
            sum = itra->data + itrb->data + carry;
        else
            sum = itra->data + carry;
        carry = sum / 10;
        sum = sum % 10;
        if (result.head == NULL)
        {
            (result.head) = newnode(sum);
            itr = result.head;
        }
        else
        {
            itr->next = newnode(sum);
            itr = itr->next;
        }
        if (itrb)
            itrb = itrb->next;
        itra = itra->next;
    }
    if (carry)
    {
        itr->next = newnode(carry);
        itr = itr->next;
    }
    // display(result);
    return result;
}
struct BigInteger add(struct BigInteger a, struct BigInteger b){
    struct BigInteger ad;
    ad = add1(a, b);
    display(ad);
    reverseLinked((&ad.head));
    return ad;
}
struct BigInteger sub1(struct BigInteger a, struct BigInteger b){
    struct BigInteger result, tempn;
    result.head = NULL;
    struct node *itr, *itra, *itrb, *temp;
    int tl, i = 0, sign = 1;
    itra = a.head;
    itrb = b.head;
    if (a.length == b.length)
    {
        while (itra != NULL)
        {
            if (itra->data < itrb->data)
            {
                i = 1;
                break;
            }
            itra = itra->next;
            itrb = itrb->next;
        }
        if (i == 1)
        {
            tempn = a;
            a = b;
            b = tempn;
            sign = -1;
        }
    }
    if (a.length < b.length)
    {
        tempn = a;
        a = b;
        b = tempn;
        tl = a.length;
        a.length = b.length;
        b.length = tl;
        sign = -1;
    }
    itra = a.head;
    itrb = b.head;
    while (itrb)
    {
        if (itra)
            if (itra->data < itrb->data)
            {
                itra->data = 10 + itra->data;
                if (itra->next)
                    itra->next->data--;
            }
        temp = newnode(itra->data - itrb->data);
        if (result.head == NULL)
        {
            result.head = temp;
            itr = temp;
        }
        else
        {
            itr->next = temp;
            itr = temp;
        }
        itra = itra->next;
        itrb = itrb->next;
    }
    i = 0;
    while (i != (a.length - b.length) && itra)
    {

        temp = newnode(itra->data);
        itr->next = temp;
        itr = temp;
        itra = itra->next;
        i++;
    }
    if (sign == -1)
        printf("-");
    return result;
}
struct BigInteger sub(struct BigInteger a, struct BigInteger b){
    struct BigInteger ad;
    ad = sub1(a, b);
    reverseLinked((&ad.head));
    ad.head = terminateZeroes(ad.head);
    return ad;
}
struct BigInteger mul1(struct BigInteger a, struct BigInteger b){
    struct BigInteger result, tempn, line1, fixed;
    result.head = line1.head = fixed.head = NULL;
    struct node *itr, *itrline, *itra, *itrb, *temp;
    int carry = 0, tl, d, p;
    if (a.length < b.length)
    {
        tempn = a;
        a = b;
        b = tempn;
        tl = a.length;
        a.length = b.length;
        b.length = tl;
    }
    itra = a.head;
    itrb = b.head;
    while (itrb)
    {
        carry = 0;
        d = itrb->data;
        itra = a.head;
        line1.head = NULL;
        while (itra)
        {
            p = (d * itra->data) + carry;
            carry = p / 10;
            p %= 10;
            temp = newnode(p);
            if (line1.head == NULL)
            {
                line1.head = temp;
                itrline = temp;
            }
            else
            {
                itrline->next = temp;
                itrline = temp;
            }
            itra = itra->next;
        }
        if (carry)
        {
            temp = newnode(carry);
            itrline->next = temp;
            itrline = temp;
        }
        if (fixed.head == NULL)
            fixed.head = line1.head;
        else
        {
            struct node *sample = line1.head;
            fixed.head = add1linked(sample, fixed.head->next);
        }
        if (result.head == NULL)
        {
            result.head = line1.head;
            itr = result.head;
        }
        else
        {
            itr->next = fixed.head;
            itr = fixed.head;
        }
        itrb = itrb->next;
    }
    return result;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b){
    struct BigInteger ad;
    ad = mul1(a, b);
    display(ad);
    reverseLinked((&ad.head));
    return ad;
}
struct node *divide1(struct node *p1, struct node *p2){
    struct BigInteger a1, b1;
    a1.head = p1;
    b1.head = p2;
    int l1, l2, i = 0, divident;
    struct node *result = NULL, *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    p1 = terminateZeroes(p1);
    p2 = terminateZeroes(p2);
    l1 = length(p1);
    l2 = length(p2);
    temp->data = 0;
    temp->next = NULL;

    if (l1 < l2)
    {
        result = temp;
        return result;
    }
    int divisor = toNumber(p2);
    int quotient, remaind;
    struct node *sampleP, *itr;
    sampleP = p1;
    int itemp = 1;
    divident = divisor;
    while (divident >= divisor)
    {
        if (result == NULL)
            divident = getdividend(&sampleP, l2);
        quotient = divident / divisor;
        remaind = divident % divisor;
        if (result == NULL)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->data = quotient;
            temp->next = NULL;
            result = temp;
            itr = result;
        }
        else
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->data = quotient;
            temp->next = NULL;
            itr->next = temp;
            itr = temp;
        }
        if (sampleP)
            divident = (remaind * 10) + (sampleP->data);
        // printf(" divident  %d", divident);
        else
            divident = remaind;
        if (sampleP)
            sampleP = sampleP->next;

        // display(result);

        itemp++;
    }
    printf("result 2 :\n");
    // display(result);
    // modulus = &remaind;
    return result;
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b){
    struct BigInteger result;
    reverseLinked(&a.head);
    reverseLinked(&b.head);
    result.head = divide1(a.head, b.head);

    result.length = length(result.head);
    reverseLinked(&a.head);
    reverseLinked(&b.head);
    return result;
}
struct BigInteger mod(struct BigInteger a, struct BigInteger b){
    struct node *itra;

    display(a);
    display(b);
    struct BigInteger divide = div1(a, b);
    // reverseLinked(&(divide.head));
    display(divide);
    reverseLinked(&divide.head);
    // reverseLinked(&b.head);
    struct BigInteger multi = mul1(divide, b);
    display(multi);
    struct BigInteger modulus = sub1(a, multi);
    reverseLinked(&modulus.head);
    modulus.head = terminateZeroes(modulus.head);
    return modulus;
}