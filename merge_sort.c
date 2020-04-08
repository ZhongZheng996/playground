#include<stdio.h>

void merge(int arr[],int l, int mid, int r)
{
    int res[10];
    int left_low = l;
    int left_high = mid;
    int right_low = mid+1;
    int right_high = r;
    int i = 0;
    while(left_low<=left_high && right_low<=right_high)
    {
        if(arr[left_low]<arr[right_low])
        {
            res[i] = arr[left_low];
            left_low++;
            i++;
        }
        else
        {
            res[i] = arr[right_low];
            right_low++;
            i++;
        }

    }
    while(left_low<=left_high)
    {
        res[i] = arr[left_low];
        i++;
        left_low++;
    }
    while(right_low<=right_high)
    {
        res[i] = arr[right_low];
        i++;
        right_low++;
    }
    for(int j = l,i = 0;j <= r;i++,j++)
        arr[j] = res[i];
}


void merge_sort(int arr[],int l,int r)
{
    if(r==l)
        return;
    else
    {
        int mid = (r+l)/2;
        merge_sort(arr,l,mid);
        merge_sort(arr,mid+1,r);
        merge(arr,l,mid,r);
    } 
}


int main(void)
{
    int a[6] = {0,-2,4,2,8,5};
    merge_sort(a,0,5);
    for(int i = 0;i<6;i++)
        printf("%d\t",a[i]);
    printf("\n");
    return 0;
}