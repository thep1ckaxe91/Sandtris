
## Architecture Optimization

In this part, we will actually read the old implementation where it only focus on MVP, but not performance, so we will be hunting "hardware terror" part that need to be re-construct for better performance.

### `std::list` in `time` namespace

If we checkout `time` namespace implementation, we will find that it heavily depend on `elapsedTimes`, which is a `std::list`. This is a cache nightmare just to check FPS or get `delta_time`.

We can instead use a ring buffer by `std::array` to store the delta time, improve cache hit also mean better performance. 

Also, rely on SDL APIs mean we possibly can't move this to SDL3 if needed, so we will utilize `std::chrono` instead.

After an afternoon of crunching **CppCon by Howard Hinnant** about `std::chrono`, i decided to refactor time namespace like this:
- unified unit `duration<float64_t, seconds>` alias `duration_t`, which fits the needs for microsec precision
- reconstruct elapsedTimes to be `std::array<duration_t, 10>` ring buffer.
- and many others, visit the commit ID to see changes in `time.hpp` and `time.cpp`

![alt text](./06-%20Refactoring%20time%20namespace.png)

What surprise me, is that a simple act of change to `std::chrono` make update cost much less compare to draw, or, maybe draw got more expensive?

Since **percentage lies**, we need a better way to check what function cost more, not just look at which bars is longer.

Current code is at: 8755abc2edf607010d51c58caee0c61e61df51a2

### Benchmarking

![alt text](./07-%20Vsync%20and%20Benchmark.png)

Turn out, the reason we got fixed at ~145 FPS is that i turned on vsync

Even when i got a result of ~6000 FPS, i wonder what if i go back to the worst implementation and just turn off vsync?

The result doesnt surprise me (benchmark_old branch):
```
draw func cost total/min/avg/max: 16.757008570970356/3.62699938705191e-06/0.00021361746686770634/0.014241922999644885
update func cost total/min/avg/max: 2.26229597627389/2.2300082491710782e-07/2.8839630516978864e-05/0.0014084920003369916
```
![alt text](./07-1%20No%20Optimization%20FPS.png)
The draw cost go up to 10ms when the screen is filled with pixels, cause me to only got ~70fps, for a retro game, this is unacceptable

Let's check out the current performance:

![alt text](./07-2%20All%20previous%20optimization%20applied.png)

We got around 6k-7k FPS, but when i capture, the game pause, so it drop to 5k

```
draw stats:
Total: 19.229804927781515
Max: 0.0024287849992106203
Min: 2.405999111942947e-06
Avg: 6.34563256592579e-05
update stats:
Total: 1.033767757624446
Max: 0.001233876002515899
Min: 2.6000634534284472e-08
Avg: 3.411324437778663e-06
event stats:
Total: 11.626231447760802
Max: 0.008018199001526227
Min: 1.0949988791253418e-06
Avg: 1.2884832161125244e-06
```

Compare that to this graph in hotspot:

![alt text](./07-3%20Hotspot%20Flame%20Graph.png)

Make complete sense, at max, update call cost ~1233us, and draw call now back to the most expensive, which is quite reasonable 

Current code is at: d05511a07d9633dd86621e3404553617356a6a3c
