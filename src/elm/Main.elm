port module Main exposing (..)

import Html exposing (Html)
import Html.Attributes as Attrs
import Html.Events as Events
import Json.Encode as Encode
import Json.Decode as Decode


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
    { title = flags.title
    , response = Nothing
    }
        ! []



-- MESSAGES


type Msg
    = SendToReason String
    | GetFromReason String



-- VIEW


view : Model -> Html Msg
view model =
    Html.div
        [ Attrs.style
            [ ( "display", "flex" )
            , ( "flex-direction", "column" )
            , ( "width", "500px" )
            ]
        ]
        [ Html.h2 [] [ Html.text model.title ]
        , Html.button [ Events.onClick <| SendToReason "Button 1" ]
            [ Html.text "Button 1" ]
        , Html.button [ Events.onClick <| SendToReason "Button 2" ]
            [ Html.text "Button 2" ]
        , Html.span [] [ Html.text <| Maybe.withDefault "" model.response ]
        ]



-- UPDATE


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        SendToReason message ->
            model ! [ infoForReason message ]

        GetFromReason s ->
            { model | response = Just s } ! []



-- PORTS


port infoForReason : String -> Cmd msg


port infoForElm : (String -> msg) -> Sub msg



-- SUBSCRIPTIONS


subscriptions : Model -> Sub Msg
subscriptions model =
    infoForElm GetFromReason



-- MAIN


main : Program Flags Model Msg
main =
    Html.programWithFlags
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        }
