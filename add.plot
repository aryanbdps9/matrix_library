set datafile separator ","
set yrange [-0.01:]
set xlabel "size"
set ylabel "time (in second)"
set key left top
set style line 1 pt 2
# set term png
set terminal pngcairo enhanced font "Times New Roman,18.0" size 1500,1100

set title 'Time vs matrix size for Addition'
set yrange [-0.01:0.15]
set output 'add_plot.png'
plot 'add.csv' u 1:2 w linespoints lw 3 title '1 thread', 'add.csv' u 1:3 w linespoints lw 3 title '2 threads', 'add.csv' u 1:4 w linespoints lw 3 title '4 threads', 'add.csv' u 1:5 w linespoints lw 3 pt 4 title '8 threads', 'add.csv' u 1:5 w linespoints lw 3 pt 6 lt '-' title '16 threads'

set yrange [-0.01:0.15]
set title 'Time vs matrix size for Division'
set output 'div_plot.png'
plot 'div.csv' u 1:2 w linespoints lw 3 title '1 thread', 'div.csv' u 1:3 w linespoints lw 3 title '2 threads', 'div.csv' u 1:4 w linespoints lw 3 title '4 threads', 'div.csv' u 1:5 w linespoints lw 3 pt 4 title '8 threads', 'div.csv' u 1:5 w linespoints lw 3 pt 6 lt '-' title '16 threads'
# pause -1

set title 'Time vs matrix size for Transpose'
# set term png
set yrange [-0.01:0.3]
set output 'transpose_plot.png'
plot 'tpose.csv' u 1:2 w l title '1 thread', 'tpose.csv' u 1:3 w l title '2 threads', 'tpose.csv' u 1:4 w l title '4 threads', 'tpose.csv' u 1:5 w l title '8 threads', 'tpose.csv' u 1:5 w l title '16 threads'
# pause -1

set title 'Time vs matrix size for Matmul'
set yrange [-0.01:1.0]
set output 'matmul_plot_3.png'
# plot 'matmul.csv' u 1:2 w linespoints lw 3 title 'matmul1', 'matmul.csv' u 1:7 w linespoints lw 3 title 'matmul2', 'matmul.csv' u 1:8 w linespoints lw 3 title 'matmul3', 'matmul.csv' u 1:9 w linespoints lw 3 title 'matmul4', 'matmul.csv' u 1:3 w linespoints lw 3 title '2 threads', 'matmul.csv' u 1:4 w linespoints lw 3 title '4 threads', 'matmul.csv' u 1:5 w linespoints lw 3 title '8 threads', 'matmul.csv' u 1:6 w linespoints lw 3 pt 6 lt '-' title '16 threads'
plot 'matmul.csv' u 1:2 w linespoints lw 3 title 'matmul1', 'matmul.csv' u 1:7 w linespoints lw 3 title 'matmul2', 'matmul.csv' u 1:8 w linespoints lw 3 title 'matmul3', 'matmul.csv' u 1:9 w linespoints lw 3 title 'matmul4', 'matmul.csv' u 1:3 w linespoints lw 3 title '2 threads', 'matmul.csv' u 1:4 w linespoints lw 3 title '4 threads', 'matmul.csv' u 1:5 w linespoints lw 3 title '8 threads', 'matmul.csv' u 1:6 w linespoints lw 3 pt 6 lt '-' title '16 threads', 'matmulfoo.csv' u 1:6 w linespoints lw 3 title 'matmul5'

set title 'Time vs matrix size for Convolution'
set yrange [-1.0:140.0]
set output 'conv_plot.png'
plot 'conv.csv' u 1:2 w linespoints lw 3 title '1 thread',\
'conv.csv' u 1:3 w linespoints lw 3 title '2 threads',\
'conv.csv' u 1:4 w linespoints lw 3 title '4 threads',\
'conv.csv' u 1:5 w linespoints lw 3 title '8 threads',\
'conv.csv' u 1:6 w linespoints lw 3 title '16 threads',\
'conv.csv'u 1:7 w linespoints lw 3 title 'conv'

# pause -1