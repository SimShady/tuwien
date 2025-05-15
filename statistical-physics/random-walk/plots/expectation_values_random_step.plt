set terminal pngcairo size 1200,600 enhanced font 'Verdana,12'
set output "plots/expectation_values_random_step.png"
set xrange [0:1000]
set yrange [-5:*]

set multiplot layout 1,2

set title "Simulation"

plot "data/expectation_values_random_step.dat" using 1:2 with lines title "{/Symbol m}", "data/expectation_values_random_step.dat" using 1:3 with lines title "{/Symbol s}"

set title "D = 0.167744"
plot sqrt(2*0.167744*x) with lines linetype 2 title "sqrt(2Dt)"

unset multiplot
set output