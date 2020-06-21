#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head){
    struct ListNode dummy;
    struct ListNode *prev;
    struct ListNode *tmp;
    struct ListNode *slow;
    struct ListNode *fast;
    
    dummy.next = head;
    slow = head;
    fast = head;
    prev = &dummy;
    while (fast != NULL)
    {
        while ((fast != NULL) && (slow->val == fast->val))
        {
            fast = fast->next;
        }
        
        if (slow->next != fast)
        {
            prev->next = fast;
            while (slow != fast)
            {
                tmp = slow;
                slow = slow->next;
                free(tmp);
            }
        }
        else
        {
            prev = slow;
            slow = fast;
        }
        
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }
    
    return dummy.next;
}
