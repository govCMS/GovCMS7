# Conventions

## Naming

- HTML elements should be in lowercase.
- Classes should be in lowercase.
- Avoid CamelCase.
- Name things clearly and semantically, by its function and not its appearance.
- Avoid presentation or location-specific words. It is preferable to be able to change a colour variable's value, and have it cascade, and not also have to change the name of the variable.
- Be wary in naming components based on content (eg `.item_list` over `.product_list`).
- Do not abbreviate, unless it is a well-known abbreviation.
- Name components and modules with singular nouns (eg `.button`).
- Name modifiers and states with adjectives (eg `.is_hovered`).
- If you intend to bring in other CSS libraries consider the namespacing carefully.
- Do not attach styles to a class prefixed with `js-` because these are reserved for JavaScript and they need to be portable.

We have opted to follow the BEM (Blocks, Elements, Modifiers) convention. For more information see [getbem.com](http://getbem.com/introduction/).

## Linting

There is `scss-lint` validation which can also be [integrated in many text editors and IDEs](https://github.com/brigade/scss-lint/#editor-integration).

We have also pulled in the KSS source in order to configure build pipelines.

## Markup

- Use HTML5, including `header`, `footer`, `article`, `section`, `aside`, `nav`.
- Use ARIA roles, eg applying `role="contentinfo"` to the page `footer`.

## Attribution

This is in part adapted from the [18F Front End Guide](https://pages.18f.gov/frontend/) under [CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/legalcode).
