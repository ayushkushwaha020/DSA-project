/* Student Record Management System - DSA Mini Project
 * Compile: gcc student_record_system.c -o student_record_system
 * Run:     ./student_record_system  (Windows: student_record_system.exe)
 * Concepts: Singly Linked List, Stack (undo), Circular Queue,
 *           Linear Search and Merge Sort.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 60
#define COURSE 40
#define QMAX 100
typedef struct Student{int roll;char name[NAME],course[COURSE];float marks;struct Student*next;}Student;
typedef enum{ADD,DEL,UPDATE}ActionType;
typedef struct Action{ActionType type;Student data;struct Action*next;}Action;
typedef struct{int roll;char text[100];}Request;
static Student*head=NULL;static Action*top=NULL;static Request queue[QMAX];static int front=0,rear=-1,qcount=0;
void line(const char*p,char*b,size_t n){int c;printf("%s",p);if(!fgets(b,(int)n,stdin)){*b=0;return;}b[strcspn(b,"\n")]=0;if(!strchr(b,'\n'))while((c=getchar())!='\n'&&c!=EOF){}}
int integer(const char*p){char b[80],x;int v;for(;;){line(p,b,sizeof b);if(sscanf(b,"%d %c",&v,&x)==1)return v;puts("Enter a valid integer.");}}
float realnum(const char*p){char b[80],x;float v;for(;;){line(p,b,sizeof b);if(sscanf(b,"%f %c",&v,&x)==1)return v;puts("Enter a valid number.");}}
void copy(Student*d,const Student*s){d->roll=s->roll;strcpy(d->name,s->name);strcpy(d->course,s->course);d->marks=s->marks;d->next=NULL;}
Student*find(int roll){Student*p=head;while(p){if(p->roll==roll)return p;p=p->next;}return NULL;}
void push(ActionType t,const Student*s){Action*a=malloc(sizeof*a);if(!a){puts("Warning: undo history unavailable.");return;}a->type=t;copy(&a->data,s);a->next=top;top=a;}
void append(const Student*s){Student*n=malloc(sizeof*n),*p;if(!n){puts("Memory allocation failed.");return;}copy(n,s);n->next=NULL;if(!head)head=n;else{p=head;while(p->next)p=p->next;p->next=n;}}
int removeNode(int roll,Student*out){Student*p=head,*prev=NULL;while(p&&p->roll!=roll){prev=p;p=p->next;}if(!p)return 0;if(out)copy(out,p);if(prev)prev->next=p->next;else head=p->next;free(p);return 1;}
void printHeader(void){printf("\n%-8s %-24s %-18s %7s\n","Roll","Name","Course","Marks");puts("------------------------------------------------------------------");}
void add(void){Student s;s.roll=integer("Roll number: ");if(s.roll<=0||find(s.roll)){puts("Roll must be positive and unique.");return;}line("Name: ",s.name,sizeof s.name);line("Course: ",s.course,sizeof s.course);s.marks=realnum("Marks (0-100): ");if(!*s.name||!*s.course||s.marks<0||s.marks>100){puts("Invalid student details.");return;}append(&s);push(ADD,&s);puts("Student added.");}
void display(void){Student*p=head;if(!p){puts("No student records.");return;}printHeader();while(p){printf("%-8d %-24s %-18s %7.2f\n",p->roll,p->name,p->course,p->marks);p=p->next;}}
void search(void){int choice=integer("1. Roll number  2. Name: ");Student*p=head;int found=0;if(choice==1){int r=integer("Roll: ");p=find(r);if(!p)puts("Not found.");else{printHeader();printf("%-8d %-24s %-18s %7.2f\n",p->roll,p->name,p->course,p->marks);}return;}if(choice==2){char q[NAME],a[NAME],b[NAME];line("Name contains: ",q,sizeof q);for(int i=0;q[i];i++)q[i]=(char)tolower((unsigned char)q[i]);while(p){strcpy(a,p->name);for(int i=0;a[i];i++)a[i]=(char)tolower((unsigned char)a[i]);strcpy(b,q);if(strstr(a,b)){if(!found)printHeader();printf("%-8d %-24s %-18s %7.2f\n",p->roll,p->name,p->course,p->marks);found=1;}p=p->next;}if(!found)puts("No matching student.");}else puts("Invalid choice.");}
void update(void){int r=integer("Roll to update: ");Student*p=find(r),old;if(!p){puts("Not found.");return;}copy(&old,p);line("New name: ",p->name,sizeof p->name);line("New course: ",p->course,sizeof p->course);p->marks=realnum("New marks: ");if(!*p->name||!*p->course||p->marks<0||p->marks>100){copy(p,&old);puts("Invalid data; old record restored.");return;}push(UPDATE,&old);puts("Updated.");}
void del(void){int r=integer("Roll to delete: ");Student s;if(!removeNode(r,&s)){puts("Not found.");return;}push(DEL,&s);puts("Deleted.");}
int before(Student*a,Student*b,int mode){return mode==1?strcmp(a->name,b->name)<=0:a->marks>=b->marks;}
Student*merge(Student*a,Student*b,int mode){Student dummy,*t=&dummy;dummy.next=NULL;while(a&&b){if(before(a,b,mode)){t->next=a;a=a->next;}else{t->next=b;b=b->next;}t=t->next;}t->next=a?a:b;return dummy.next;}
Student*sortList(Student*p,int mode){Student*slow,*fast,*right;if(!p||!p->next)return p;slow=p;fast=p->next;while(fast&&fast->next){slow=slow->next;fast=fast->next->next;}right=slow->next;slow->next=NULL;return merge(sortList(p,mode),sortList(right,mode),mode);}
void sort(void){int m=integer("1. Name A-Z  2. Marks high-low: ");if(m!=1&&m!=2){puts("Invalid choice.");return;}head=sortList(head,m);display();}
void undo(void){Action*a=top;if(!a){puts("Nothing to undo.");return;}top=a->next;if(a->type==ADD)removeNode(a->data.roll,NULL);else if(a->type==DEL)append(&a->data);else{Student*p=find(a->data.roll);if(p)copy(p,&a->data);}free(a);puts("Undo completed.");}
void enqueue(void){if(qcount==QMAX){puts("Queue full.");return;}Request r;r.roll=integer("Student roll: ");line("Request: ",r.text,sizeof r.text);if(!*r.text){puts("Request cannot be empty.");return;}rear=(rear+1)%QMAX;queue[rear]=r;qcount++;puts("Request queued.");}
void process(void){if(!qcount){puts("Queue empty.");return;}Request r=queue[front];front=(front+1)%QMAX;qcount--;printf("Processed roll %d: %s\n",r.roll,r.text);}
void queueView(void){if(!qcount){puts("No pending requests.");return;}for(int i=0;i<qcount;i++){int k=(front+i)%QMAX;printf("%d. Roll %d - %s\n",i+1,queue[k].roll,queue[k].text);}}
void stats(void){Student*p=head;int n=0,pass=0;float total=0,hi=-1,lo=101;if(!p){puts("No records.");return;}while(p){n++;total+=p->marks;if(p->marks>=40)pass++;if(p->marks>hi)hi=p->marks;if(p->marks<lo)lo=p->marks;p=p->next;}printf("Students: %d | Average: %.2f | Highest: %.2f | Lowest: %.2f | Pass: %d | Fail: %d\n",n,total/n,hi,lo,pass,n-pass);}
void cleanup(void){while(head){Student*p=head;head=head->next;free(p);}while(top){Action*a=top;top=top->next;free(a);}}
int main(void){int c;do{puts("\n==== STUDENT RECORD MANAGEMENT SYSTEM ====");puts("1 Add  2 Display  3 Search  4 Update  5 Delete");puts("6 Merge sort  7 Undo (Stack)  8 Add request (Queue)");puts("9 Process request  10 View requests  11 Statistics  0 Exit");c=integer("Choice: ");switch(c){case 1:add();break;case 2:display();break;case 3:search();break;case 4:update();break;case 5:del();break;case 6:sort();break;case 7:undo();break;case 8:enqueue();break;case 9:process();break;case 10:queueView();break;case 11:stats();break;case 0:puts("Goodbye.");break;default:puts("Invalid choice.");}}while(c!=0);cleanup();return 0;}