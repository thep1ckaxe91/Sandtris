### No optimization

![no opt image](01-%20No%20Optimization.png)

Look at the flame graph, we can see libgallium is screaming with thousands of draw call

We can fix that by draw all to a streaming texture first, then to the main window texture later

Current code is at: 834816a344eed54964034a92c5edceeb87bb585b

### Texture lock optimized

![Tex lock](02-%20Texture%20Lock%20Optimized.png)

Compare to the previous graph where the draw function cost 9-10x of the update function, now they are mostly equally the same.

But now, we expose more flaws in the draw call:
- The ::at is showing possible improvement, since im using std::map, which is absolutely not necessary, we can fix this by using std::array instead
- Im clearing the streaming texture, which is quite wrong, and also doing unnecessary calculation for no sand cell


Current code is at: 648c55803b4015028f394ece587be643ae17f128


### `Grid::draw` calculation optimized

![grid draw cal](03-%20Grid::draw%20calculation%20Optimized.png)

The total cost of draw function is now so low, that update cost is doubled the cost of the draw itself

It's time to hunt the update function side

One weird thing i found, is that `Button::update` is even more expensive than `Animation::update`. Why?

Because if we looking at `Button::handle_event` in `Button.cpp`, we are copying the entire texture every time we move over (hover) a button, or click a button, this cost is super dodgable if we just use a pointer instead of copy the entire texture. (std::move time)

Actually, if we look at the animation spike, we also found `Surface::operator=` as a bottle neck too, since in the update function, it also constantly copying surface.

So let's do one thing, that is create a move operator for surface and ultilize it everywhere i should

Current code is at: 673510e49a20314843ec09425acbe1de716736a8

### `Surface` move semantics

![Surface move](./04-%20Surface%20move%20semantics.png)

Saying this is optimized by move semantic is kind of a scam, of course, looking at the result, we clearly see the spike literally disappear while the game rans fine, but for a different reason

My old code is so scrap, all i was doing was just literally change the way `Sprite` class works, i change from leaving the entire `Sprite::image` as a `Surface` to a pointer instead, and refactor all where it use `Sprite::image`

So all those optimization was just pointers, no move involve, but i guess we can save move for another optimization later on.

Focus on the update func, there're 2 main spike:
- `Grid::update_ghost_shape` (on the left of `redraw`)
- `TetriminoController::redraw` (which update the shape of the tetrimino "but only when it rotate")

But that's the thing, `redraw` only needed when rotate, but in `update` (which call every frame), i left it call `redraw` for some reason, so I simply remove it and do a quick re-profiling

![Remove redraw call](./04-1%20Remove%20unnecessary%20redraw%20call.png)

Which make the spike disappear completely. At this point, some how when remove `clock.tick`, it still only run at 150FPS.

Current code is at: 9f71107279e2c116a669ba27cae06e2d2cd25c29

### Ghost draw optimization


![alt text](./05-%20Remove%20unnecessary%20update%20ghost%20shape.png)

Just same as before, there was a unnecessary `Grid::update_ghost_shape` call from update func which call every frame

Simple as remove it, we now make the update function which before about equal to draw cost, now only 1/3 of it.

All above which:
- Reduce draw cost by 1/10
- Reduce update cost by 1/3

Was already **~30 times** faster main loop

Current code is at: 