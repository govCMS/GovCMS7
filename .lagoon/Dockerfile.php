ARG CLI_IMAGE
FROM ${CLI_IMAGE:-cli} as cli

FROM amazeeio/php:7.1-fpm

COPY --from=cli /app/docroot /app/docroot
