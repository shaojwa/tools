when a line starts with `@`, the echoing of that line is suppressed.
```
@echo debug:incdir: $(INCDIR)
```
the `@` is discarded before the line to passed to shell.
