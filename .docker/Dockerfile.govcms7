FROM amazeeio/php:7.1-cli-drupal as builder

COPY . /src

RUN rm -rf /app \
    && cd /src \
    && echo "memory_limit=-1" >> /usr/local/etc/php/conf.d/memory.ini \
    && drush make /src/.docker/stub.make /app --contrib-destination \
	&& cp /app/sites/default/default.settings.php /app/sites/default/settings.php \
	&& { \
		echo ; \
		echo "\$databases['default']['default'] = array ("; \
		echo "  'driver' => 'mysql',"; \
		echo "  'database' => getenv('MARIADB_DATABASE') ?: 'drupal',"; \
		echo "  'username' => getenv('MARIADB_USERNAME') ?: 'drupal',"; \
		echo "  'password' => getenv('MARIADB_PASSWORD') ?: 'drupal',"; \
		echo "  'host' => getenv('MARIADB_HOST') ?: 'mariadb',"; \
		echo "  'port' => '3306',"; \
		echo "  'prefix' => '',"; \
		echo ");"; \
		echo ; \
		echo "\$drupal_hash_salt = getenv('DRUPAL_HASH_SALT') ?: 'changeme';"; \
    } | tee -a "/app/sites/default/settings.php" \
    && chmod 444 /app/sites/default/settings.php

FROM amazeeio/php:7.1-cli-drupal

RUN apk add gmp gmp-dev \
    && docker-php-ext-install gmp \
    && docker-php-ext-configure gmp

COPY --from=builder /app /app
