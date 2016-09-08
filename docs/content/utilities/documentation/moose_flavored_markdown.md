# MOOSE Flavored Markdown

Documentation generated using MOOSE is generated using the [python-markdown](http://pythonhosted.org/Markdown/) package,
which includes the ability to use extensions from others as well as define custom extensions. This page outlines the
extensions included as well as the custom syntax defined exclusively for documenting MOOSE source code.

---

## Extensions
### Symbol Conversion
This package converts ASCII symbols for dashes, quotes, and ellipses to the correct html, for more information see the
documentation for this package: [SmartyPants](http://pythonhosted.org/Markdown/extensions/smarty.html).

### Markdown Include
This package allows for other markdown file to be include within the current file by enclosing the markdown file to
be included within \{\! and \!\}. For more information refer to the package documentation: [markdown-include](https://github.com/cmacmackin/markdown-include).

### Mathematics
The enables the use of [MathJax](http://www.mathjax.org) within markdown, refer to the package documentation for complete
details: [python-markdown-math](https://github.com/mitya57/python-markdown-math).

Inline math may be specified by enclosing the latex in single `$`: $y=a\cdot x + b$. Addtionally, stand-alone math may
be enclosed in `$$`:

$$
x=\frac{1+y}{1+2z^2}.
$$

### Admonition
The [admonition](https://pythonhosted.org/Markdown/extensions/admonition.html) package enables for important and critical
items to be highlighted, using the syntax detailed below and the package documentation: [admonition](https://pythonhosted.org/Markdown/extensions/admonition.html).

```markdown
!!! type "An optional title"
    A detailed message paragraph that is indented by 4 spaces and can include any number of lines.
```

The supported "types" for MOOSE are: "info", "note", "important, "warning", "danger", and "error."

!!! info "Optional Info Title"
    This is some information you want people to know about.

!!! note "Optional Note Title"
    This is an example of a note.

!!! important "Optional Important Title"
    This is an example of something important.

!!! warning "Optional Warning Title"
    This is a warning.

!!! danger "Optional Danger Title"
    This is something very dangerous.

!!! error "Optional Error Title"
    This is an error message.

---

## Automatic Links

Moose Flavored Markdown is capable of automatically creating links based on Markdown filenames, which is
especially useful when linking to generated pages. The syntax is as follows:

* `[auto::/Kernels/Diffusion]`: [auto::/Kernels/Diffusion]
* `[auto::framework/Kernels/Overview]`: [auto::/Kernels/Overview]
* `[Diffusion](auto::/Kernels/Diffusion)`: [Diffusion](auto::/Kernels/Diffusion)

---

## Including MOOSE Source Files
It is possible to include complete or partial C++ or input files from the local MOOSE repository. The following sections detail the custom
markdown syntax to needed, including the application of special settings in the form of key, value pairings that are supplied within
the custom markdown. A complete list of available settings is provided in the [Settings](MooseFlavoredMarkdown.md#optional-settings) of the included code.

### Complete Files
You can include complete files from the repository using the `!text` syntax. For example, the following
includes the complete code as shown.

```markdown
!text framework/src/kernels/Diffusion.C max-height=200px strip-extra-newlines=True
```

!text framework/src/kernels/Diffusion.C max-height=200px strip-extra-newlines=True

### Single Line Match
It is possible to show a single line of a file by a snippet that allows the line to be located within
the file. If multiple matches occur only the first match will be shown. For example, the call to
`addClassDescription` can be shown by adding the following.

```markdown
!text framework/src/kernels/Diffusion.C line=addClassDescription
```

!text framework/src/kernels/Diffusion.C line=addClassDescription

### Range Line match
Code starting and ending on lines containing a string is also possible by using the 'start' and 'end'
options. If 'start' is omitted then the snippet will start at the beginning of the file. Similarly, if 'end'
is omitted the snippet will include the remainder of the file content.

```markdown
!text test/tests/kernels/simple_diffusion/simple_diffusion.i start=Kernels end=Executioner
```

!text test/tests/kernels/simple_diffusion/simple_diffusion.i start=Kernels end=Executioner

### Class Methods
By including a method name, in C++ syntax fashion, it is possible to include specific methods from C++ classes in MOOSE. For example,
the following limits the included code to the `computeQpResidual` method.

```markdown
!clang framework/src/kernels/Diffusion.C method=computeQpResidual
```
!clang framework/src/kernels/Diffusion.C method=computeQpResidual

!!! warning "Warning"
    This method uses the clang parser directly, which can be slow. Thus, in general source code should be
    included using the line and range match methods above and this method reserved for cases where those methods
    fail to capture the necessary code.


### Input File Block
By including a block name the included content will be limited to the content matching the supplied name. Notice that the supplied name may be approximate; however, if it is not unique only the first match will appear.

```markdown
!input test/tests/kernels/simple_diffusion/simple_diffusion.i block=Kernels
```

!input test/tests/kernels/simple_diffusion/simple_diffusion.i block=Kernels

### Optional Settings
The following options may be passed to control how the output is formatted.


| Option               | Default | Description |
| -------------------- | ------- | ----------- |
| strip_header         | True    | Toggles the removal of the MOOSE copyright header. |
| repo_link            | True    | Include a link to the source code on GitHub ("label" must be True). |
| label                | True    | Include a label with the filename before the code content block. |
| overflow-y           | Scroll  | The action to take when the text overflow the html container (see [overflow-y](http://www.w3schools.com/cssref/css3_pr_overflow-y.asp)). |
| max-height           | 500px   | The maximum height of the code window (see [max-height](http://www.w3schools.com/cssref/pr_dim_max-height.asp)). |
| strip-extra-newlines | False   | Remove excessive newlines from the included code. |

---

## Slideshows
A sequence of images can be shown via a `carousel`. By default the images will auto cycle between images.

A simple example:

```markdown
!slideshow
    images/intro.png
    images/other*.png
```

This would create a slideshow with the first image as `intro.png` and the next images those that are matched by the wildcard `other*.png`.

Valid options for the slideshow are the same as for the `bootstrap` [carousel](http://getbootstrap.com/javascript/#carousel):

| Option               | Default | Description |
| -------------------- | ------- | ----------- |
| interval             | 5000    | The amount of time delay between images, in milliseconds. |
| pause                | hover   | If set to "hover" then the carousel will pause when the mouse is moved over it. |
| wrap                 | true    | If true then the carousel will cycle continuously. |
| keyboard             | true    | If true then the carousel will respond to keyboard events. |

Additionally, a `caption` option can be set globally or for each image line. The global caption will be used if no caption is specified on the image
line.

A full slideshow example might be:
```markdown
!slideshow caption=My caption with spaces interval=1000 pause=null wrap=false keyboard=false
    images/intro.png caption=Introduction image
    images/other*.png caption=Other images
    images/more*.png
```

---

## Images
You can include images in your documentation by use of the !image markdown syntax:

```markdown
!image memory_logger-plot_multi.png width=300 align=right caption=Figure 1
```
!image memory_logger-plot_multi.png width=300 align=right caption=Figure 1

---

## Flow Charts
The ability to include diagrams using [GraphViz](http://www.graphviz.org/) using the [dot]() language is provided.
Simply, include the "dot" syntax in the markdown, being sure to include the keywords ("graph" or
"digraph") on the start of a new line.

* The official page for the dot language is detailed here: [dot](http://www.graphviz.org/content/dot-language)
* There are many sites that provide examples, for example:
    * [https://en.wikipedia.org/wiki/DOT_(graph_description_language)](https://en.wikipedia.org/wiki/DOT_(graph_description_language))
    * [http://graphs.grevian.org/example](http://graphs.grevian.org/example)
* There also exists live, online tools for writing dot:
    * [http://dreampuf.github.io/GraphvizOnline/](http://dreampuf.github.io/GraphvizOnline/)
    * [http://www.webgraphviz.com/](http://www.webgraphviz.com/)

For example, the following dot syntax placed directly in the markdown produces the following graph.
```text
graph {
    bgcolor="#ffffff00" // transparent background
    a -- b -- c;
    b -- d;
}
```

graph {
    bgcolor="#ffffff00" // transparent background
    a -- b -- c;
    b -- d;
}