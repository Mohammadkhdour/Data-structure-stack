//Name:Mohammad Barhom Harbe Khdour
//ID:1212517
//Section:2

#include <stdio.h>
#include <stdlib.h>

typedef struct node* ptrToNode;
typedef ptrToNode Stack;
struct node{
    char data;
    ptrToNode next;
};

void Reader(Stack equations[]);
Stack createStack();
void push(Stack s, char element);
char pop(Stack stack);
char top(Stack stack);
int isEmpty(Stack stack);
void makeEmpty(Stack stack);
Stack reverseStack(Stack stack);
void printStack(Stack stack);
int countEquationsInFile(FILE *A);
int priority(char c);
int isNum(char c);
Stack convertToPrefix(Stack equations);
int evaluatePrefix(Stack stack);
int isEquationValid(Stack stack[],int size);
int isValid(Stack stack);
Stack copyStack(Stack stack);
int check_2(Stack stack);
int check_3(Stack stack);
int check_1(Stack stack);
int check_4(Stack stack);
Stack reversePow(Stack stack);
void menu();
void selectOperation(Stack equations[],int size);
void printInFill(Stack stack[],int size);

FILE *input,*output;

int main() {
    int size=countEquationsInFile(input);
    Stack equations[size];
    for (int i = 0; i <size ; ++i) {
        equations[i]=createStack();
    }
    printf("the is %d equations in file\n",size);
    selectOperation(equations,size);

    return 0;
}
void menu(){
    printf("\nselect operation:\n");
    printf("1_read from file\n");
    printf("2_check the validity for equations\n");
    printf("3_convert valid equations to prefix\n");
    printf("4_evaluate prefix\n");
    printf("5_print invalid equation\n");
    printf("6_print all equation in file\n");
    printf("7_exit\n");
}
void selectOperation(Stack equations[],int size){//to select operation we want
    int x;
    int one=0;//read one time from file
    do {
        menu();//display menu of operation
        scanf("%d",&x);//select operation from user
        switch (x) {
            case 1://print equation which exist in file
            if(one++==0)
                Reader(equations);
                for (int i = 0; i < size; ++i)
                    printStack(reverseStack(equations[i]));
                break;
            case 2://print the validity of equation
                isEquationValid(equations, size);
                break;
            case 3://convert to prefix
                for (int i = 0; i < size; ++i)
                    if (isValid(equations[i]))
                        printStack(convertToPrefix(equations[i]));
                break;
            case 4://print the result of equation if it valid
                for (int i = 0; i < size; ++i)
                    if (isValid(equations[i]))
                        printf("the result %d_ %d\n", i+1, evaluatePrefix(convertToPrefix(equations[i])));

                break;
            case 5: //print invalid equation
                for (int i = 0; i < size; ++i)
                    if (!isValid(equations[i]))
                        printStack(reverseStack(equations[i]));
                break;
            case 6://print the result in file
                printInFill(equations,size);
                break;
            case 7://exit from system
                printf("the system will closed. good bye");
                exit(0);

        }
    } while (x);
}
void Reader(Stack equations[]){//function read from file
    char name [20];
    printf("enter file name\n");
    scanf("%s",name);
     input= fopen(name,"r");
    if(input==NULL){//check if the file exist or not
        printf("file doesn't exist\n");
        exit(-1);
    }
    char c;
    char ch[30];
    int count=0;
    while ((c=fgetc(input))!=EOF){//read character by character and put the in stack
        if(c=='\n') {
            count++;
            continue;
        }//converts all pow
        if(c==')')
            push(equations[count],'(');
        else if(c=='(')
            push(equations[count],')');
        else if(c=='[')
            push(equations[count],']');
        else if(c==']')
            push(equations[count],'[');
        else
        push(equations[count],c);

    }
    fclose(input);//close file
}

Stack createStack(){//crate new stack
    Stack stack;
    stack=( Stack) malloc(sizeof(Stack));
    if(stack==NULL)//check if it out of memory
        printf("out of memory");

    stack->next=NULL;
    return stack;
}

void push(Stack stack, char element){//insertion function for stack
    ptrToNode newNode;
    newNode=(Stack) malloc(sizeof(Stack));
    if(newNode==NULL)
        printf("out of memory");
    else {
        newNode->data = element;
        newNode->next = stack->next;
        stack->next = newNode;
    }
}

char pop(Stack stack){//deletion function for stack
    char x;
    if(isEmpty(stack)) {
        printf("stack is empty");
        return '\0';
    }
        ptrToNode firstCell=stack->next;
        x = firstCell->data;
        stack->next = stack->next->next;
          //  free(firstCell);
            firstCell=NULL;

    return x;
}
char top(Stack stack){//return top value
    if(!isEmpty(stack))
        return stack->next->data;
    return '\0';
}
int isEmpty(Stack stack){//check if stack empty or not
    return stack->next==NULL;
}
void makeEmpty(Stack stack){//delete all node in stack
    if(stack==NULL)
        printf("the stack doesn't exist");
    else
        while(!isEmpty(stack))
            pop(stack);
}
void printStack(Stack stack){//print the value in stack
    Stack cop= copyStack(stack);
    while (!isEmpty(cop)) {
        printf("%c", pop(cop));
    }
    printf("\n");
}
void printInFill(Stack stack[],int size){//print stack in output file
    output= fopen("output","w");
    if(output==NULL) {
        printf("error couldn't open file");
        return;
    }
    for (int i = 0; i < size; ++i) {//loop to print the parameter list which contains the results
        Stack current = copyStack(stack[i]);
        if(isValid(current)) {
            fprintf(output,"%d_valid ",i+1);//print valid equation
            current = convertToPrefix(current);//make current equal prefix
            fprintf(output," the result =%d\t prefix= ", evaluatePrefix(current));//print valid equation
            while (!isEmpty(current)) {
                fprintf(output, "%c", pop(current));//print prefix expression in file
            }
        } else
            fprintf(output,"%d_invalid ",i+1);//print invalid equation
        fprintf(output,"\n");
    }
}
Stack copyStack(Stack stack){//return new stack equal parameter stack
    Stack cop=createStack();
    Stack temp=createStack();
    while (!isEmpty(stack)){
        push(temp,pop(stack));
    }
    while ((!isEmpty(temp))){
        push(stack, top(temp));
        push(cop, pop(temp));
    }
    makeEmpty(temp);
    return cop;
}

int countEquationsInFile(FILE *A){//count number of equation in file it is size of array
      char name [20];
   printf("enter file name to count number of equation\n");
   scanf("%s",name);
    A= fopen(name,"r");
    if (A==NULL){
        printf("the file which you search about doesn't exist!!!");
        exit(-1);
    }
    int count= 0;
    char x[30];
    while(fscanf(A,"%s",x)!=EOF){
        count++;
    }
    fclose(A);
    return count;
}
int isNum(char c){//check if character is number or not
    if(c>='0'&&c<='9')
        return 1;
    else
        return 0;
}
int priority(char c){//priority of operation
    if(c=='+' || c=='-')//lowest priority
        return 1;
    else if (c=='*' || c=='/')//highest priority
        return 2;
    else//not operation
        return 0;
}
int mathOperation(int op1,int op2,char op){//make addition or sub or mult or div between two number
    if(op=='+')
        return op1+op2;
    else if(op=='-')
        return op1-op2;
    else if(op=='*')
        return op1*op2;
    else if(op=='/')
        return op1/op2;
    else return 0;
}
Stack reverseStack(Stack stack){//return new Stack and return reverse of parameter stack
    Stack cop= copyStack(stack);
    Stack rev=createStack();
    char ch;
    while(!isEmpty(cop)){
        ch= pop(cop);
        if(ch=='(')
            push(rev,')');
        else if(ch==')')
            push(rev,'(');
        else if(ch=='[')
            push(rev,']');
        else if(ch==']')
            push(rev,'[');
        else
        push(rev, ch);
    }
    return rev;
}

int evaluatePrefix(Stack stack){//evaluate prefix expression
    Stack st=createStack();//stack which have final result
    Stack cop= reverseStack(stack);
    int result;
    char ch;
    while(!isEmpty(cop)) {
        ch= pop(cop);
        if(isNum(ch))
            push(st,ch);
        else {
            int op1 = pop(st)-'0';
            int op2 = pop(st)-'0';

            result = mathOperation(op1, op2, ch);
            push(st,result+'0');
        }

    }
    return result;
}
Stack convertToPrefix(Stack equations){//convert from equation to prefix
    Stack cop= copyStack(equations);
    Stack prefix=createStack();
    Stack operation=createStack();
    char ch;
        while (!isEmpty(cop)){//check if stack which have equation is not NULL
            ch= pop(cop);
            if(isNum(ch)){//if ch is number push in prefix stack
                push(prefix,ch);
            }
            else if (ch=='('||ch=='['){//else if ch open pri-cat push it in operation stack
                push(operation,ch);
            }
            else if(ch==')'){//else if close pri-cat push all character between open and close pri cat
                while (top(operation)!='('){
                    push(prefix, top(operation));
                    pop(operation);
                }
                pop(operation);
            }
            else if(ch==']'){//else if close pri-cat push all character between open and close pri cat
                while (top(operation)!='['){
                    push(prefix, top(operation));
                    pop(operation);
                }
                pop(operation);
            }
            else{//check the negative sign for numbers
                if(ch=='-'&& top(cop)=='-'){
                    ch='+';
                    pop(cop);
                }
                else if(ch=='-'&& top(cop)=='+'){
                    ch='-';
                    pop(cop);
                }
                else if(ch=='+'&& top(cop)=='-'){
                    ch='-';
                    pop(cop);
                }
                else if(ch=='+'&& top(cop)=='+'){
                    ch='+';
                    pop(cop);
                }
                while(priority(top(operation))>= priority(ch)){//if the priority in stack operation highest from ch print the highest priority in prefix
                    push(prefix, top(operation));
                    pop(operation);
                }
                push(operation,ch);
            }

        }

        while (!isEmpty(operation)){//print the remain characters in operation stack in prefix stack
            push(prefix, pop(operation));
        }
    return prefix;
}
int isEquationValid(Stack stack[],int size){
    for (int i = 0; i < size; ++i) {
           if (check_1(stack[i])==0)
               printf("equation %d-invalid ( is not closed!!\n", i + 1);

           else if(check_2(stack[i])==0)
               printf("equation %d-invalid there is two operation together!!\n", i + 1);

           else if(check_3(stack[i])==0)
               printf("equation %d-invalid there is no operation as x[!!\n", i + 1);

           else
               printf("equation %d-valid\n",i+1);
    }
    return 1;
}
int isValid(Stack stack){
    if (check_1(stack)&&check_2(stack)&&check_3(stack))
        return 1;
    else
        return 0;
}
int check_2(Stack stack) {//check if there are two highest operation together
    Stack cop= copyStack(stack);
    char ch;
    while (!isEmpty(cop)) {
        ch= pop(cop);
        if (priority(ch) ==2 && priority(pop(cop)) >0)
            return 0;
    }
    return 1;
}
int check_3(Stack stack){//check if there is no operation between practice and number
    Stack cop= copyStack(stack);
    char ch;
    while (!isEmpty(cop)){
        ch= pop(cop);
        if(ch=='('||ch=='[') {
            if (priority(top(cop))==2)
                return 0;
        }
        else if (priority(ch)==2) {
            if (top(cop) == ')' || top(cop)==']')
                return 0;
        }
        else if((ch==']'||ch==')')&&isNum(top(cop)))
            return 0;

    }
    return 1;
}
int check_1(Stack stack){//check pri cat
    Stack copy= copyStack(stack);
    Stack opera=createStack();//stack have all pri-cat
    Stack temp=createStack();
    char ch;
    while(!isEmpty(copy)){
        ch= pop(copy);
        if(ch=='('||ch==')'|| ch=='['||ch==']')
            push(opera,ch);//push pri-cat in opera stack
    }
    while (!isEmpty(opera)) {
        ch = pop(opera);
        if (ch == ']') {
            while (!isEmpty(opera)&&(ch= pop(opera))!= '[') {
                push(temp,ch);
            }
            while(!isEmpty(opera))
                push(temp, pop(opera));
            if(ch=='[') {
                opera= reversePow(temp);
                if(!isEmpty(temp))
                makeEmpty(temp);
            }else
                return 0;
        }

        else if (ch == ')') {
            while (!isEmpty(opera)&&(ch= pop(opera))!= '(') {
                push(temp,ch);
            }
            while(!isEmpty(opera))
                push(temp, pop(opera));

            if(ch=='(') {
                opera= reversePow(temp);
                if(!isEmpty(temp))
                makeEmpty(temp);
            }else
                return 0;
        } else
            return 0;
    }
    return 1;
}
Stack reversePow(Stack stack){
    Stack cop= copyStack(stack);
    Stack rev=createStack();
    while(!isEmpty(cop)){
            push(rev, pop(cop));
    }
    return rev;
}
int check_4(Stack stack){
    Stack cop= copyStack(stack);
    Stack pri=createStack();
    char ch;
    while (!isEmpty(cop)){
        ch= pop(cop);
        if(isNum(ch)|| priority(ch)>0)
            continue;

        if(ch=='('||ch=='[')
            push(pri,ch);
        else if( ch==')'&& top(pri)!='(' ||ch==']'&& top(pri)!='[')
            return 0;
        else
            pop(pri);
    }
    if(!isEmpty(pri))
        return 0;
    return 1;
}