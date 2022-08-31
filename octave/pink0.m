t=0:99

x = rand(100)
subplot(2,1,1)
plot(t,x)
grid
xlabel("Time in milliseconds")
ylabel("Signal amplitude")

subplot(2,1,2)
y=fft(x)
plot(t,abs(y))
xlabel("Frequency")
ylabel("Signal amplitude")
