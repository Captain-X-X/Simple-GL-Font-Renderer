this should work for windows, but I only tested on ArchLinux...

make sure to download Glad, GLM, stb_truetype & some font(s).


How to use:

1st.
```
  FFont font;
  font.loadFont("some/ttf/font.ttf");
  
  if(!FontRenderer::Initilize(&font))
  {
      printf("Failed to initilize font renderer\n");
      return -1;
  }

  unsigned int fontSHader;
  fontSHader = font.fontShader;

```

2nd. aka in some render loop
```
  glUseProgram(fontSHader);
  FontRenderer::Begin();
  render();
  FontRenderer::End();
  FontRenderer::Flush();

```
