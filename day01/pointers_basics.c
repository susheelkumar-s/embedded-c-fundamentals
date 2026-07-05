#include <stdio.h>
#include <stdint.h>

//1:Swaping two integers using pointers
void swap(int *a, int *b) // consider two pointers to integers i.e *a and *b as a parameters. 
{
    int temp = *a;//Dereferencing the pointer a to get the value of a and storing it in temp
    *a = *b; //Dereferencing the pointer b to get the value of b and storing it in a
    *b = temp; //Storing the value of temp in b
}

//2:Find integer array max using pointer travel
int find_max(int *arr, int siz)
{
    int max = *arr;
    for (int i=1; i<siz; i++)
    {
        if(*(arr+i)>max)//Dereferencing the pointer arr+i to get the value of the element at index i and comparing it with max
        {
            max = *(arr+i);// alternative : if (arr[i] > max) max = arr[i]; 
        }
    }
    return max;
}

//3:Strlen function using pointer travel
int my_strlen(char *str)
{
    int len = 0;
    while(*str != '\0')//Dereferencing the pointer str to get the value of the character and checking if it is not null character
    {
        len++;
        str++;//Incrementing the pointer str to point to the next character in the string
    }
    return len;
}

//4:Implementing memcpy using pointer function and casting
void *my_memcpy(void *dest, const void *src, int n)
{
    uint8_t *d = (uint8_t *)dest;//Casting the void pointer dest to uint8_t pointer d
    const uint8_t *s = (const uint8_t *)src;//const preserves the value of src and prevents it from being modified.
    while(n--)
    {
        *d++ = *s++;//Dereferencing d to get the value and store, then incrementing both pointers d and s.
    }
    return dest;
}

//5:Reverse a string in place using pointer travel
void reverse_string(char *str)
{
    char *start = str;
    char *end = str + my_strlen(str) - 1;
    while(start < end)
    {
        char temp = *start;// we can't use swap() function here because it is for integersr, not for characters.
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

//6:Return multiple values from a function using pointer parameters
void get_min_max(int *arr, int siz, int *min, int *max)
{
    *min = *arr;
    *max = *arr;
    //*min = *max = arr[0]; // alternative way to initialize min and max
    for (int i=1; i<siz; i++)
    {
        if(*(arr+i)<*min)
        {
            *min = *(arr+i);// alternative : if (arr[i] < *min) *min = arr[i];
        }
        if(*(arr+i)>*max)
        {
            *max = *(arr+i);// alternative : if (arr[i] > *max) *max = arr[i];
        }
    }
}

//7:Function Pointer example
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
//int (*operation)(int, int);
//8:Array of function pointers example.

//9:Struct with pointer members example
typedef struct
{
    char *name;   // Pointer to a string
    int *values;  // Pointer to an integer array
    int count;
} DataBuffer;



//0:Main function
int main()
{
    //Calling swap function
    printf("\nCalling swap function:\n");
    int x = 10, y = 20;
    printf("Before swapping: x = %d, y = %d\n", x, y);
    swap(&x, &y); //Passing the address of x and y to the swap function
    printf("After swapping: x = %d, y = %d\n", x, y);

    //Calling find_max function
    printf("\nCalling find_max function:\n"); 
    int readings[] = {1, 2, 3, 6, 4, 2, 5};
    int size = sizeof(readings) / sizeof(readings[0]);
    int max_reading = find_max(readings, size);// "readings" equivalent to &readings[0] to the comp
    printf("Maximum reading: %d\n", max_reading); 
    
    //Calling my_strlen function
    printf("\nCalling my_strlen function:\n");
    char str[] = "Look at me! There is nothing in my heart.";
    int length = my_strlen(str);
    printf("Length of the string: %d\n", length);

    //Calling my_memcpy function
    printf("\ncalling My_memcpy function\n");
    char src1[] = "I am the strongest in the whole world now!";
    char dest1[50];
    my_memcpy(dest1, src1,sizeof(src1));
    printf("copied bytes including null terminator: %s\n", dest1);

    //Calling reverse_string function
    printf("\nCalling reverse_string function:\n");
    char str1[] = "Hello";
    printf("Before: %s\n", str1);   // Hello
    reverse_string(str1);
    printf("After:  %s\n\n", str1); // olleH

    //Calling get_min_max function
    printf("\nCalling get_min_max function:\n");
    int arr[] = {5, 2, 9, 1, 7};
    int min, max; //Memory allocated but stores garbage values
    get_min_max(arr, sizeof(arr)/sizeof(arr[0]), &min, &max); 
    printf("Minimum: %d, Maximum: %d\n", min, max);

    //Function pointer example
    printf("\nFunction pointer example:\n");
    int (*operation)(int, int);//Declare a Function pointer with the same parameter and return type as the functions add and multiply.
    operation = &add;//"&" is optional in c //Assign the address of the add function to the function pointer.
    printf("Addition: %d\n", operation(5, 3)); //Calling the add function using the function pointer.
    operation = &multiply;
    printf("Multiplication: %d\n", operation(5, 3));

    //8: Array of function pointers example
    int (*ops[3])(int, int) = {add, sub, multiply}; //Array of function pointers
    printf("\nArray of function pointers example:\n");
    for(int i=0; i<3; i++)
    {
        printf("Result of operation %d: %d\n", i, ops[i](10, 5)); //Calling the functions using the array of function pointers.
    }

    //9: Struct with pointer members example
    printf("\nStruct with pointer members example:\n");
    int numbers[] = {1, 2, 3, 4, 5};
    DataBuffer data;
    data.name = "Sensor1";
    data.values = numbers;
    data.count = sizeof(numbers) / sizeof(numbers[0]);
    printf("DataBuffer name: %s\n", data.name);
    for(int i=0; i<data.count; i++)
    {
        printf("Value %d: %d\n", i, data.values[i]);
    }

    
    


    return 0;
}