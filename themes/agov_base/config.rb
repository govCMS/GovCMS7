# Require any additional compass plugins here.

# Set this to the root of your project when deployed:
http_path = "/"

# Directories
css_dir = "css"
sass_dir = "sass"
images_dir = "images"
javascripts_dir = "js"
fonts_dir = "fonts"

# Other options
relative_assets = true
line_comments = false
color_output = false

# Don't add cache-busing hash's to generated image urls
asset_cache_buster :none

# Leave this as expanded for now.
output_style = :expanded

# Uncomment the line below to output debug info your css files.
# Be sure to re-comment it before commiting.
# sass_options = {:debug_info => true}

# If you prefer the indented syntax, you might want to regenerate this
# project again passing --syntax sass, or you can uncomment this:
# preferred_syntax = :sass
# and then run:
# sass-convert -R --from scss --to sass sass scss && rm -rf sass && mv scss sass
preferred_syntax = :scss

# Require any additional compass plugins installed on your system.
require 'breakpoint'
