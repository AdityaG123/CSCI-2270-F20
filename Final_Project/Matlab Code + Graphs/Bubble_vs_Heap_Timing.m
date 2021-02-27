clc 
close all 
clear all

Bubble_Sort = csvread('insert_sort_performance_bubblesort_dataSetA.csv');
Heap_Sort = csvread('insert_sort_performance_heapsort_dataSetA.csv');
col1 = Bubble_Sort(:, 1);
col2 = Heap_Sort(:,1);
x = 1:1:100;
plot(x, col1)
hold on
plot(x, col2)
xlabel('Iterations');
ylabel('Time');
title('Performance of Bubble Sort vs Heap Sort Timing');
legend('Bubble Sort', 'Heap Sort');