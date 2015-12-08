chunks = 0
logtrials = 0
if length(ARGS) > 0
   logtrials = parse(Int, ARGS[1])
end
if logtrials <= 0
   logtrials = 4
end

if length(ARGS) > 1
   chunks = 2^parse(Int, ARGS[2])
end
if chunks <= 0
   chunks = 2^15
end


@everywhere function doTrials(trials)
   count  = 0
   points = rand(trials,2)
   for i = 1:trials
      count += (points[i,1]^2 + points[i,2]^2 <= 1.0)
   end
   count
end

println("Estimating pi with ", 2^logtrials, " iterations...")
tic()

roundedup = 2^logtrials + (chunks - ((2^logtrials) % chunks))
count = @parallel (+) for i=1:chunks:roundedup
   doTrials(chunks)
end
elapsed = toq()
estimate = float(count) / float(2^logtrials) * 4.0

println("\tEstimate of pi is ", estimate)
println("\tTook ", elapsed, " s: ", (float(roundedup) * 1.0e-6 * 6.0) / elapsed, " MFlop/s")
