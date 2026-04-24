# asepbens.in

A personal website written in C. Yes, C. The language your professor warned you about.

No React. No Next.js. No 847 npm packages just to render a div. Just raw, unhinged C code serving HTML over HTTP like it's 1999 — except it actually works and loads faster than your average "modern" web app.

**Live site:** [asepbens.in](https://asepbens.in)

---

## Why

Because everyone told me to use a JavaScript framework, and I have a problem with authority.

Also because I wanted my personal site to be smaller than the average `node_modules` folder. The bar was underground and I still had to dig.

---

## Tech Stack

| Layer | Choice | Justification |
|-------|--------|---------------|
| Server | C + libmicrohttpd | I enjoy suffering |
| Interactivity | HTMX | Because 14KB > 140KB of React |
| Styling | Hand-written CSS | Tailwind is for quitters |
| JavaScript | Vanilla, no framework | npm install? Never heard of it |
| Templating | Custom C string replacement | Why use Jinja when you can segfault |
| Font | Courier New (system) | Zero external requests. You're welcome, Google Fonts |
| Build tool | make | Webpack can stay in the shadow realm |

Total external dependencies: **one** (libmicrohttpd). That's it. My `package.json` is a `Makefile` and it has 12 lines.

---

## Features

### The Normal Ones

- SPA-like navigation powered by HTMX (full page loads for SEO, fragment swaps for speed)
- Responsive design with a terminal-themed mobile menu (`$ ls ~/`)
- Custom `{{body}}` templating engine written in C because I don't value my time
- OpenGraph and Twitter Card meta tags (I'm unhinged, not unprofessional)

### The Unhinged Ones

- **rm -rf / button** — A glowing red button in the corner. Click it. Everything falls off the screen. You asked for this.
- **Shutdown button that runs away** — Try to click it. It dodges your cursor. Corner it and it teleports. The profile photo gets angry at you for trying. You will never catch it.
- **Logo held together by duct tape** — Hover over it and the tape breaks. The logo falls. A tiny hand slides in from the left to tape it back. This took longer to code than the actual server.
- **Custom right-click menu** — Replaces your browser's context menu with a terminal-themed one. Options include `rm -rf /`, `cat source.c`, and `steal design` (greyed out, obviously).
- **Konami Code** — Up Up Down Down Left Right Left Right B A. Activates Comic Sans mode. You have been warned.
- **Idle terminal** — Stop moving for 30 seconds and the terminal starts typing passive-aggressive messages at you. "still here?" "go touch grass" "malloc failed. just like my life."
- **Fake contact form** — Looks real. Isn't. SMTP connection refused. Just DM me on Instagram like a normal person.
- **Angry profile photo** — Chase the shutdown button and the profile photo shakes and yells at you. Lines include "this is harassment" and "I will mass segfault on you."
- **Keyboard shortcuts** — 1, 2, 3 to navigate. D to destroy everything. Documented in the nav because I'm a gentleman.
- **"Don't click this" button** — It's a Rick Roll. You were warned.

---

## Project Structure

```
.
|-- main.c            # Entry point. Starts the server. Waits for you to press Enter. That's it.
|-- handlers.c/.h     # Route handlers. The closest thing this project has to a "controller."
|-- html.c/.h         # The "templating engine." It finds {{body}} and replaces it. Revolutionary.
|-- file_utils.c/.h   # Reads files. Into strings. Groundbreaking computer science.
|-- Makefile           # 12 lines of build instructions. Shorter than most README files.
|-- templates/
|   |-- layout.html    # The main layout. 1200+ lines. Most of it is easter eggs.
|   |-- home.html      # Home page content
|   |-- about.html     # About/resume page
|   |-- contact.html   # The fake contact form lives here
|   |-- 404.html       # "cat: /page: No such file or directory"
|-- assets/
|   |-- htmx.min.js    # The only JS dependency. Self-hosted because I trust no CDN.
```

---

## Routes

| Route | What it does |
|-------|-------------|
| `/` | Home page. Has a terminal widget. Judges you if you're idle. |
| `/about` | My resume in terminal format. `cat resume.txt` |
| `/contact` | A contact form that doesn't work. On purpose. |
| `/home-frag` | Home fragment for HTMX. You don't need to know this. |
| `/about-frag` | About fragment for HTMX. Same. |
| `/contact-frag` | Contact fragment for HTMX. Stop reading. |
| `/js/htmx.min.js` | Serves HTMX. The only JavaScript I respect. |
| `/*` | 404. "Looks like this page segfaulted into the void." |

---

## Build & Run

### Prerequisites

You need `libmicrohttpd`. Install it like a civilized person:

```bash
# Arch (btw)
sudo pacman -S libmicrohttpd

# Debian/Ubuntu
sudo apt install libmicrohttpd-dev

# macOS (if you must)
brew install libmicrohttpd
```

### Build

```bash
make
```

That's it. No `npm install`. No 5-minute build step. No webpack config that looks like it was written by a committee.

### Run

```bash
./server
```

Server starts on port `8080`. Press Enter to stop it. Revolutionary UX.

---

## FAQ

**Q: Why didn't you use React/Next.js/Svelte/Vue/Astro/[insert framework]?**
A: Because my website loads in under 50ms and yours doesn't.

**Q: Is this production ready?**
A: It's in production right now. Define "ready."

**Q: How do I contribute?**
A: You don't. This is a personal website. But if you find a segfault, that's a feature.

**Q: Why is the layout.html file 1200+ lines?**
A: Easter eggs are expensive. Also I don't believe in separating concerns when the concern is chaos.

**Q: Does the contact form actually work?**
A: No. SMTP connection refused. Relay denied. Server said: "nah." Just DM me.

**Q: Why C?**
A: Why not? The real question is why everyone else is shipping 2MB of JavaScript to display text on a screen.

---

## Performance

| Metric | This site | Average React app |
|--------|-----------|-------------------|
| JS bundle size | 14KB (HTMX) | lol |
| node_modules | 0 | 847 packages |
| Build time | ~0.3s | go make coffee |
| Time to interactive | instant | still loading... |
| Framework updates to worry about | 0 | yes |

---

## License

Do whatever you want with it. If you steal my design, the right-click menu already called you out.

But seriously, if this inspires you to write a web server in C, seek help. Or don't. I'm not your therapist.

---

*Made with pain using C programming language.*
