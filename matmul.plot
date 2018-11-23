set datafile separator ","
set yrange [-0.01:1]
set xlabel "size"
set ylabel "time (in second)"
plot 'matmul.csv' u 1:2 w l title 'matmul1', 'matmul.csv' u 1:3 w l title '2 threads', 'matmul.csv' u 1:4 w l title '4 threads', 'matmul.csv' u 1:5 w l title '8 threads', 'matmul.csv' u 1:6 w l title '16 threads', 'matmul.csv' u 1:7 w l title 'matmul2', 'matmul.csv' u 1:8 w l title 'matmul3', 'matmul.csv' u 1:9 w l title 'matmul4', 
pause -1