ARG CODE_IMAGE
FROM ${CODE_IMAGE} as code

FROM amazeeio/php:7.1-fpm
COPY --from=code /app /app
