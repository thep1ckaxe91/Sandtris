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

Current code is at: