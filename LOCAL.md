# govCMS Local Environment Setup

## Local environment setup
1. Make sure that you have [Docker](https://www.docker.com/), [Pygmy](https://docs.amazee.io/local_docker_development/pygmy.html) and [Ahoy](https://github.com/ahoy-cli/ahoy)installed.
2. Checkout project repository
3. `ahoy build`
4. `ahoy install`
5. http://govcms.docker.amazee.io

## List of available Ahoy workflow commands:

```
   build                Build project.
   cli                  Start a shell inside CLI container.
   cli-run              Run command inside CLI container.
   docker-logs          Show Docker logs.
   docker-ps            List running Docker containers.
   docker-pull          Pull latest Docker containes.
   docker-restart       Restart Docker containers.
   docker-start         Start Docker containers.
   docker-stop          Stop Docker containers.
   drush                Run drush commands in the CLI service container.
   info                 Show site information.
   install-dependencies Install dependencies.
   install-site         Install the website.
   login                Login to a website.  
```
