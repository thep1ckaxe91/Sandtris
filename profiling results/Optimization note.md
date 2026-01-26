### No optimization

![no opt image](./01-%20No%20Optimization.png)

Look at the flame graph, we can see libgallium is screaming with thousands of draw call

We can fix that by draw all to a streaming texture first, then to the main window texture later

Current code is at: 834816a344eed54964034a92c5edceeb87bb585b

### Texture lock optimized

![Tex lock](./02-%20Texture%20Lock%20Optimized.png)

Compare to the previous graph where the draw function cost 9-10x of the update function, now they are mostly equally the same.

But now, we expose more flaws in the draw call:
- The ::at is showing possible improvement, since im using std::map, which is absolutely not necessary
- Im clearing the streaming texture, which is quite wrong, and also doing unnecessary calculation for no sand cell

