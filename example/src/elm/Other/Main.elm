port module Other.Main exposing (Flags, Model, Msg(..), infoForElm, infoForReason, init, main, subscriptions, update, view)

import Browser
import Html exposing (Html)
import Html.Attributes as Attrs
import Html.Events as Events
import Json.Decode as Decode
import Json.Encode as Encode



-- MODEL


type alias Model =
    { title : String
    , response : Maybe String
    }


type alias Flags =
    { title : String
    }


init : Flags -> ( Model, Cmd Msg )
init flags =
    ( { title = flags.title
      , response = Nothing
      }
    , Cmd.none
    )



-- MESSAGES


type Msg
    = SendToReason String
    | GetFromReason String



-- VIEW


view : Model -> List (Html Msg)
view model =
    [ Html.div
        [ Attrs.style "display" "flex"
        , Attrs.style "flex-direction" "column"
        , Attrs.style "width" "500px"
        ]
        [ Html.h2 [] [ Html.text model.title ]
        , Html.button [ Events.onClick <| SendToReason "Button 1" ]
            [ Html.text "Button 1" ]
        , Html.button [ Events.onClick <| SendToReason "Button 2" ]
            [ Html.text "Button 2" ]
        , Html.span [] [ Html.text <| Maybe.withDefault "" model.response ]
        ]
    ]



-- UPDATE


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        SendToReason message ->
            ( model
            , infoForReason message
            )

        GetFromReason s ->
            ( { model | response = Just s }
            , Cmd.none
            )



-- PORTS


port infoForReason : String -> Cmd msg


port infoForElm : (String -> msg) -> Sub msg



-- SUBSCRIPTIONS


subscriptions : Model -> Sub Msg
subscriptions model =
    infoForElm GetFromReason



-- MAIN


main =
    Browser.document
        { init = init
        , view =
            \model ->
                { title = "BS Elm Example"
                , body = view model
                }
        , update = update
        , subscriptions = subscriptions
        }
