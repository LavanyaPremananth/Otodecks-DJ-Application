# Otodecks - DJ Application

Otodecks is a feature-rich DJ application developed as part of an Object-Oriented Programming coursework. This document outlines the features, requirements, and implementation details of the project.

## Features

- **Basic Functionality**:
  - Load audio files into audio players.
  - Play two or more tracks simultaneously.
  - Mix tracks by adjusting their volumes.
  - Speed up or slow down tracks.

- **Custom Deck Control Component**:
  - Implements custom graphics for advanced playback control.
  - Enables user interaction beyond basic start/stop.

- **Music Library Component**:
  - Manage music library by adding files.
  - Display metadata such as filename and song length.
  - Search for files within the library.
  - Load files from the library into audio decks.
  - Persistent library data across application sessions.

- **Custom GUI Layout**:
  - Unique GUI design with extra controls.
  - Integrates custom components for enhanced functionality.

## Implementation Details

### Deck GUI (DeckGUI Class)

- Utilizes `AudioTransportSource` for audio playback control.
- Implements custom sliders using `setSliderStyle()` for volume and speed controls.
- Controls playback position with `setPositionRelative()`.

### Custom Deck Control Component

- Custom graphics implemented using a `paint` function.
- Provides advanced playback controls for enhanced user experience.

### Music Library Component (PlaylistComponent Class)

- File management features to add, parse, and display audio files.
- Includes a search box (`searchingTextBox`) for efficient file search.
- Ensures music library data persistence for seamless user experience.

### Custom GUI Layout

- Extends beyond basic DeckGUI with additional controls.
- Integrates custom components and music library features into a cohesive UI.

## Usage

To use Otodecks:
1. Clone the repository.
2. Set up the project in your preferred IDE.
3. Run the application and explore its features.
