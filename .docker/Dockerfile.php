ARG CLI_IMAGE
FROM ${CLI_IMAGE} as cli

FROM uselagoon/php-7.4-fpm

COPY --from=cli /app /app
