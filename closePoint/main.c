//
//  main.c
//  closePoint
//
//  Created by wupeng on 2017/5/28.
//  Copyright © 2017年 wupeng. All rights reserved.
//

#include <stdio.h>
struct point {
    int x, y;
};

double distance(struct point a, struct point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void QuickSort(struct point *arr, int left, int right) {
    //如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
    if(left >= right){
        return ;
    }
    int i = left;
    int j = right;
    int key = arr[left].y;
    /*控制在当组内寻找一遍*/
    while(i < j){
        //而寻找结束的条件就是，
        //1，找到一个小于或者大于key的数（大于或小于取决于你想升序还是降序）
        //2，没有符合条件1的，并且i与j的大小没有反转
        while(i < j && key <= arr[j].y){
            //向前寻找
            j--;
        }
        //找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        // a[left]，那么就是给key）
        arr[i] = arr[j];
        
        while(i < j && key >= arr[i].y){
            //这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
            //因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i].y = key;/*当在当组内找完一遍以后就把中间数key回归*/
    QuickSort(arr, left, i - 1);//最后用同样的方式对分出来的左边的小组进行同上的做法
    QuickSort(arr, i + 1, right);//用同样的方式对分出来的右边的小组进行同上的做法
    /*当然最后可能会出现很多分左右，直到每一组的i = j 为止*/
}

double closest (struct point S[], int low, int high) {
    double d1, d2, d3, d;
    int mid, i, j, index;
//    存放集合P1和P2
    struct point P[high];
//    只有两个点，返回两点间的距离
    if (high - low == 1) {
        return distance(S[low], S[high]);
    }
//    只有三个点。求最经对的距离
    if (high - low == 2) {
        d1 = distance(S[low], S[low + 1]);
        d2 = distance(S[low + 1], S[high]);
        d3 = distance(S[low], S[high]);
        if (d1 < d2 && d1 < d3) {
            return d1;
        } else if (d2 < d3) {
            return d2;
        } else {
            return d3;
        }
    }
//    计算中间点
    mid = (low + high) / 2;
//    递归求解子问题1
    d1 = closest(S, low, mid);
//    递归求解子问题2
    d2 = closest(S, mid + 1, high);
//    以下为求解子问题3
    d = d1 <= d2 ? d1 : d2;
    index = 0;
//    建立集合P1
    for (i = mid; i >= low && S[mid].x  - S[i].x < d2; i--) {
        P[index++] = S[i];
    }
//    建立集合P2
    for (i = mid + 1; i < high && S[i].x - S[mid].x < d; i++) {
        P[index++] = S[i];
    }
//    对P1和P2按照按照y升序排列
    QuickSort(P, 0, index - 1);
    for (i = 0; i < index; i++) {
        for (j = i +1; j < index; j++) {
            if (P[j].y - P[i].y >= d) {
//                超出y坐标范围，处理完毕
                break;
            } else {
                d3 = distance(P[i], P[j]);
                if (d3 < d) {
                    d = d3;
                }
            }
        }
    }
    return d;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
