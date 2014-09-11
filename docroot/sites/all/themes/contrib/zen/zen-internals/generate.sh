#!/bin/bash

# This script is used by the MAINTAINERS to generate the CSS files from the Sass
# files and make copies of the STARTERKIT stylesheets for the base Zen theme.


ORIG=`pwd`;
STARTERKIT=../STARTERKIT;


# Change directory to the STARTERKIT and run compass with a custom config.
cd $STARTERKIT;
cp config.rb config.rb.orig;
echo "asset_cache_buster :none" >> config.rb;
compass clean;

# Create our custom init partial, while keeping the original.
mv sass/_init.scss $ORIG/;
cat $ORIG/_init.scss $ORIG/extras/sass/_init_extras.scss > sass/_init.scss;

# Build the stylesheets for the Zen base theme.
cp $ORIG/extras/sass/styles-fixed* sass/;
compass compile --environment production --no-line-comments --output-style compressed;
rm sass/styles-fixed*;

# Copy the stylesheets from STARTERKIT to the Zen theme.
rm $ORIG/css/*.css;
rm $ORIG/images/*;
cp css/styles* $ORIG/css/;
cp images/* $ORIG/images/;

# Build the CSS versions of the stylesheets.
cp $ORIG/extras/sass/css-* sass/;
cp $ORIG/extras/sass/layouts/css-* sass/layouts/;
cp $ORIG/extras/sass/components/css-* sass/components/;
rm css/*.css css/*/*.css;
compass clean;
compass compile --no-line-comments;
rm sass/css-* sass/*/css-*;

# Don't use the generated styles.css.
git checkout css/styles.css css/styles-rtl.css;

# Massage the generated css-* files and rename them.
for FILENAME in css/css-*.css css/*/css-*.css; do
  NEWFILE=`echo $FILENAME | sed -e 's/css\-//'`;

  cat $FILENAME |
  # Ensure each selector is on its own line.
  sed -e 's/^\(\@media.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\(\@media.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\(\@media.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\(\/\*.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\(\/\*.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\(\/\*.*\), /\1FIX_THIS_COMMA /' |
  sed -e 's/^\([^ ].*\), /\1,\
/' |
  sed -e 's/^\([^ ].*\), /\1,\
/' |
  sed -e 's/^\([^ ].*\), /\1,\
/' |
  sed -e 's/^\([^ ].*\), /\1,\
/' |
  sed -e 's/FIX_THIS_COMMA/,/' |
  sed -e 's/FIX_THIS_COMMA/,/' |
  sed -e 's/FIX_THIS_COMMA/,/' |
  sed -e '/: /! s/^\(  [^ /].*\), /\1,\
  /' |
  # Fix IE wireframes rules.
  sed -n '1h;1!H;$ {g;s/\.lt\-ie8\n/.lt-ie8 /g;p;}' |
  # Move notation comments back to the previous line with the property.
  sed -e 's/^ \{2,4\}\(\/\* [1-9LTR]* \*\/\)$/  MOVE_UP\1/' |
  sed -n '1h;1!H;$ {g;s/\n  MOVE_UP/ /g;p;}' |
  # Remove blank lines
  sed -e '/^$/d' |
  # Add a blank line between a block-level comment and another comment.
  sed -n '1h;1!H;$ {g;s/\(\n *\*\/\n\)\( *\)\/\*/\1\
\2\/\*/g;p;}' |
  # Add a blank line between a ruleset and a comment.
  sed -n '1h;1!H;$ {g;s/\(\n *\}\n\)\( *\)\/\*/\1\
\2\/\*/g;p;}' |
  # Add a blank line between the start of a media query and a comment.
  #@media all and (min-width: 480px) and (max-width: 959px) {
  sed -n '1h;1!H;$ {g;s/\(\n\@media .* .\n\)\(  \/\**\)/\1\
\2/g;p;}' |
  # Remove any blank lines at the end of the file.
  sed -n '$!p;$ {s/^\(..*\)$/\1/p;}' |
  # Remove the second @file comment block in RTL layout files.
  sed -n '1h;1!H;$ {g;s/\n\/\*\*\n \* \@file\n[^\/]*\/\/[^\/]*\n \*\/\n//;p;}' |
  # Convert 2 or more blank lines into 1 blank line and write to the new file.
  cat -s > $NEWFILE;

  rm $FILENAME;
done

# Update the comments in the layouts/*-rtl.css files.
for FILENAME in css/layouts/*-rtl.css; do
  cat $FILENAME |
  sed -e 's/from left\. \*\/$/FIX_THIS/' |
  sed -e 's/from right\. \*\/$/from left. *\//' |
  sed -e 's/FIX_THIS$/from right. *\//' |
  sed -e 's/ the left one\.$/FIX_THIS/' |
  sed -e 's/ the right one\.$/ the left one./' |
  sed -e 's/FIX_THIS$/ the right one./' |
  cat > $FILENAME.new;
  mv $FILENAME.new $FILENAME;
done

for FIND_FILE in $ORIG/extras/text-replacements/*--search.txt $ORIG/extras/text-replacements/*/*--search.txt; do
  REPLACE_FILE=`echo "$FIND_FILE" | sed -e 's/\-\-search\.txt/--replace.txt/'`;
  CSS_PATH=`dirname $FIND_FILE`;
  CSS_PATH=css/`basename $CSS_PATH`;
  if [[ $CSS_PATH == 'css/text-replacements' ]]; then CSS_PATH=css; fi
  CSS_FILE=$CSS_PATH/`basename $FIND_FILE | sed -e 's/\-\-.*\-\-search\.txt/.css/'`;

  # Convert search string to a sed-compatible regular expression.
  FIND=`cat $FIND_FILE | perl -e 'while (<>) { $_ =~ s/\s+$//; $line = quotemeta($_) . "\\\n"; $line =~ s/\\\([\(\)\{\}])/\1/g; print $line}'`;

  cat $CSS_FILE |
  # Replace search string with "TEXT-REPLACEMENT" token.
  sed -n -e '1h;1!H;$ {g;' -e "s/$FIND/TEXT\-REPLACEMENT/;" -e 'p;}' |
  sed -e 's/TEXT\-REPLACEMENT/TEXT\-REPLACEMENT\
/' |
  # Replace "TEXT-REPLACEMENT" token with contents of replacement file.
  sed -e "/^TEXT-REPLACEMENT\$/{r $REPLACE_FILE" -e 'd;}' | #-e '/^TEXT-REPLACEMENT$/! d;' |
  cat > $CSS_FILE.new;

  # Halt the script if no replacement has been made.
  if [ -z "`diff -q $CSS_FILE $CSS_FILE.new`" ]; then
    echo "FATAL ERROR: The following file contents were not found: `basename $FIND_FILE`";
    # Delete all the generated CSS, except for the one that generated the error.
    rm css/*.css $ORIG/css/*.css;
    mv $CSS_FILE.new $CSS_FILE;
    # Restore the environment.
    mv config.rb.orig config.rb;
    mv $ORIG/_init.scss sass/;
    exit;
  fi

  mv $CSS_FILE.new $CSS_FILE;
done

# Restore the environment.
mv config.rb.orig config.rb;
mv $ORIG/_init.scss sass/;
cd $ORIG;
