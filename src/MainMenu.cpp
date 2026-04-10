#include "MainMenu.hpp"
#include "constant.hpp"
#include "SaveData.hpp"
MainMenu::MainMenu(Game &game) : Scene(game)
{

    if (have_grid_data())
    {
        resume_button = ResumeButton(game);
        resume_button.rect.setTopLeft(8, RESOLUTION_HEIGHT - 8 * 4 - 16 * 4);
        can_resume = 1;
    }
    else
        can_resume = 0;

    start_button = StartButton(game);
    start_button.rect.setTopLeft(8, RESOLUTION_HEIGHT - 8 * 3 - 16 * 3);
    credit_button = CreditButton(game);
    credit_button.rect.setTopLeft(8, RESOLUTION_HEIGHT - 8 * 2 - 16 * 2);
    quit_button = QuitButton(game);
    quit_button.rect.setTopLeft(8, RESOLUTION_HEIGHT - 8 - 16);

    pb_button = PBButton(game);
    pb_button.rect.setTopLeft(119 - 32 - 2, 104);
    htp_button = HTPButton(game);
    htp_button.rect.setTopLeft(119, 104);
    option_button = OptionButton(game);
    option_button.rect.setTopLeft(119 - 64 - 4, 104);

    sdlgame::music::load(base_path + "assets/audio/music/mainmenu_theme_loop.mp3");
    sdlgame::music::play(-1, 1000);
}
void MainMenu::handle_event(Event &event)
{
    start_button.handle_event(event);
    quit_button.handle_event(event);
    credit_button.handle_event(event);
    pb_button.handle_event(event);
    htp_button.handle_event(event);
    option_button.handle_event(event);
    if (can_resume)
        resume_button.handle_event(event);
}
void MainMenu::update()
{
    start_button.update();
    quit_button.update();
    credit_button.update();
    pb_button.update();
    htp_button.update();
    option_button.update();
    if (can_resume)
        resume_button.update();
}
void MainMenu::draw()
{
    game->window.blit(game->images.mainmenu_background, math::Vector2());
    game->window.blit(*start_button.image, start_button.rect.getTopLeft());
    game->window.blit(*credit_button.image, credit_button.rect.getTopLeft());
    game->window.blit(*quit_button.image, quit_button.rect.getTopLeft());
    game->window.blit(*pb_button.image, pb_button.rect.getTopLeft());
    game->window.blit(*htp_button.image, htp_button.rect.getTopLeft());
    game->window.blit(*option_button.image, option_button.rect.getTopLeft());
    if (can_resume)
        game->window.blit(*resume_button.image, resume_button.rect.getTopLeft());
}
MainMenu::~MainMenu()
{
}