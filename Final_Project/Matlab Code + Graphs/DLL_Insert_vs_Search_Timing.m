clc 
close all 
clear all

DLL = csvread('insert_search_performance_doubly_ll_dataSetA.csv');
col1 = DLL(1, :);
col2 = DLL(2, :);
x = 1:1:100;
plot(x, col1)
hold on
plot(x, col2)
xlabel('Iterations');
ylabel('Time');
title('Performance of DLL Insert vs Search Timing');
legend('DLL Insert', 'DLL Search');