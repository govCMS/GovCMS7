FROM amazeeio/php:7.1-fpm
COPY --from=govcms/govcms7 /app /app
