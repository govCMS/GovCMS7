ARG CLI_IMAGE
FROM ${CLI_IMAGE} as cli

FROM amazeeio/php:7.1-fpm

RUN apk add gmp gmp-dev \
    && docker-php-ext-install gmp \
    && docker-php-ext-configure gmp

COPY --from=cli /app /app
