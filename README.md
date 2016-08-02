# A small C template renderer
C program to render a template file with replacement keys. Templates look like:

    Hello {{name}}!

Words inside `{{}}` will be replaced with values given as arguments, like this:

    ./template_renderer templateFile.hsh replacementKey: replacementValue anotherKey: anotherValue

You can specify as many replacements as you want as arguments, in the form `replacementName: replacementValue`
