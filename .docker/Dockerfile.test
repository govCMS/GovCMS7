ARG CLI_IMAGE
FROM ${CLI_IMAGE} as cli

FROM amazeeio/php:7.1-cli-drupal

ENV DOCKERIZE_VERSION v0.6.1
RUN wget https://github.com/jwilder/dockerize/releases/download/$DOCKERIZE_VERSION/dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
    && tar -C /usr/local/bin -xzvf dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz \
    && rm dockerize-alpine-linux-amd64-$DOCKERIZE_VERSION.tar.gz

COPY tests/composer.json tests/composer.lock /app/tests/

RUN echo "memory_limit=-1" >> /usr/local/etc/php/conf.d/memory.ini \
    && composer install -d /app/tests -n --ansi --prefer-dist --no-suggest \
    && drush dl drupalorg_drush-7.x-1.x-dev -y \
    && rm -rf /usr/local/etc/php/conf.d/memory.ini

COPY --from=cli /app /app

COPY tests /app/tests

RUN mv /app/profiles/govcms/.docker/lint-govcms /usr/bin/lint-govcms \
    && chmod +x /usr/bin/lint-govcms \
    && mv /app/profiles/govcms/.docker/lint-theme /usr/bin/lint-theme \
    && chmod +x /usr/bin/lint-theme \
    && mv /app/profiles/govcms/.docker/behat /usr/bin/behat \
    && chmod +x /usr/bin/behat \
    && mv /app/profiles/govcms/.docker/phpunit /usr/bin/phpunit \
    && chmod +x /usr/bin/phpunit
