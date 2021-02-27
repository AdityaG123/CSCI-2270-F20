clc 
close all 
clear all

Heap_Sort = csvread('insert_sort_performance_heapsort_dataSetA.csv');
col1 = Heap_Sort(:, 1);
x = 1:1:100;
plot(x, col1)
xlabel('Iterations');
ylabel('Time');
title('Performance of Heap Sort Timing');
legend('Heap Sort Time');