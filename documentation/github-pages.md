---
title: Github Pages
---

# Using and Contributing to the Github Pages

These docs are created via Github Pages' default Jekyll configuration, allowing markdown (`.md`) files to be automatically pre-rendered into HTML.
This also allows us to use liquid/HTML include and layout files to generate consistent styling across our site without dynamic inclusion via JS or some other method.

#### If your goal is only to write standard documentation then there are only a couple things you need to do:

1. Make a new `.md` file in the appropriate category folder

	For example, experience setting up on a Mac system might be called `mac-setup.md` and go under the `setup` folder.

2. Add the frontmatter to your new page:

	```md
	---
	title: Great Page
	---

	#My Great Page With A Long Name

	Blah, blah blah.
	```

3. Make your changes

	Text can be typed directly into the markdown, with standard formatting.

	Images should be placed into `assets/images/` and referenced via relative paths.

#### If you want to make deeper changes to the site such as adding categories, changing themeing, modifiying the navigation, etc; you should know a bit more:

1. The appearance of all the pages currently on this site are controlled by the `_layouts/default.html` layout file. If any different layouts are needed in the future they should be added to this file.

2. The navbar is a custom element from `_includes/navigation.html` and is very liquid reliant to generate the nav data. Nav entries are added by modifying the `_config.yml` with an addition to the `navigation` list with a link and name.

3. Any HTML rendered by Jekyll including the layouts and includes can use the liquid language to extend the functionality of HTML with iteration, pulling data about the current page, etc.

4. Any subpages of a new navbar element must be layed out in a directory of the same name for the linking and navigation to work correctly.

5. You should locally render and test any substantial changes to layouts, includes, or site structure. These are the steps you will need to do so:

	- Install Ruby version 3.2.4, either directly or via [rbenv](https://github.com/rbenv/rbenv). Prexisting `.ruby-version` in the repo should allow rbenv to automatically detect the needed version.
		For rbenv to run the install command you must install ruby-build, and the dependencies for the ruby build process. Pacman command for Arch systems:
		
		`pacman -S --needed base-devel rust libffi libyaml openssl zlib ruby-build ruby-erb`

	- Run several commands to get the repo setup for serving the webpage locally:

		`gem install bundler`

		`bundle install`

	- Serve the webpage locally:

		`bundle exec jekyll serve`

		This will serve the site on `localhost:4000` with dynamic reload enabled. If you edit a content file (not the `_config.yml`) and save Jekyll should automatically rerender and display those changes.		