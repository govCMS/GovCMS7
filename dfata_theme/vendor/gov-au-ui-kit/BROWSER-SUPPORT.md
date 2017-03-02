# Browser support

The UI-Kit team needs to support all of our users, regardless of their device, web browser or other user agent.

Equal access to information about laws and government programs is a legal requirement under the <a href="https://www.legislation.gov.au/Latest/C2016C00763" rel="external">Disability Discrimination Act (1992)</a>.

The support levels will be revised when needed to better meet user needs.

We initially defined these levels using analytics data from various major \*.gov.au sites.

## Mobile browsers

| Browser        | Platforms      | Minimum version | Advanced support status              |
|----------------|----------------|-----------------|-----------------------|
| Chrome         | Android, iOS   | 21              | Tested (Android only) |
| Firefox        | Android, iOS   | 28              | Untested              |
| Safari         | iOS            | 3.2             | Untested              |
| Android browser| Android        | 2.1             | Untested              |
| IE             | Windows Mobile | 10              | Untested              |

Minimum version based on [support for CSS Flexible Box layout modules](http://caniuse.com/#feat=flexbox).

## Desktop browsers

| Browser           | Platforms     | Advanced support status |
|-------------------|---------------|-------------|
| Chrome            | Windows, OS X | Tested      |
| Firefox           | Windows, OS X | Tested      |
| Safari            | OS X          | Untested    |
| Opera             | Windows, OS X | Untested    |
| Yandex            | Windows, OS X | Untested    |
| Edge              | Windows       | Untested    |
| IE 10 & newer            | Windows       | Tested      |
| IE 9 & older      | Windows       | Tested &mdash; functional support only  |

All browsers listed are latest stable release, except Internet Explorer.

## Unsupported browsers

We don’t list unsupported devices and browsers.

We are aiming for a solid HTML mobile-first foundation that provides functional support for the browsers and devices of all of our users.

## Advanced support

* All (or most) documented features.
* Advanced functionality and behaviour.
* Advanced design using JavaScript and CSS.

## Functional support

* Accessible content.
* Users can complete critical tasks.
* Basic page design and layout, based on the simplest layout available to graphical browsers.
* Similar look and behaviour across all pages (performance will still vary across browsers).
* JavaScript and CSS not necessarily required.

As we perform browser testing we will provide component-specific documentation. This will specify what is critical and what provides advanced functionality.

## Principles

1. Support basic access and functionality in the browsers and devices of all of our users.
2. Build a solid semantic HTML5 foundation.
3. <a href="https://en.wikipedia.org/wiki/Progressive_enhancement" rel="external">Progressive enhancement</a> over <a href="https://en.wikipedia.org/wiki/Fault_tolerance" rel="external">graceful degradation</a>. Build the basic foundation for the lowest common denominator then enhance &mdash; instead of a managed degraded experience for older browsers (fault tolerance).

We define ‘support’ as:

- making things usable before they go live
- improving and fixing issues found in production environments.

We didn’t use a decision tree because:

- we can identify fully supported browsers and devices
- all other browsers and devices need graduated support.
