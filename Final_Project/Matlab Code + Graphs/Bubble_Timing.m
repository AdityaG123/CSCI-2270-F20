clc 
close all 
clear all

Bubble_Sort = csvread('insert_sort_performance_bubblesort_dataSetA.csv');
col1 = Bubble_Sort(:, 1);
x = 1:1:100;
plot(x, col1)
xlabel('Iterations');
ylabel('Time');
title('Performance of Bubble Sort Timing');
legend('Bubble Sort Time');