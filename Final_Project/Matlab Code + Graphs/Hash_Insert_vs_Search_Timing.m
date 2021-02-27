clc 
close all 
clear all

Hash = csvread('insert_search_performance_hash_dataSetA.csv');
col1 = Hash(1, :);
col2 = Hash(3, :);
x = 1:1:100;
plot(x, col1)
hold on
plot(x, col2)
xlabel('Iterations');
ylabel('Time');
title('Performance of Hash Insert vs Search Timing');
legend('Hash Insert', 'Hash Search');